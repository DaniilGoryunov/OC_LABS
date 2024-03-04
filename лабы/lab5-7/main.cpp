#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <thread>
#include <chrono>
#include "control_node.h"

using namespace lab;

const int ATTEMPT_HEARTBIT_COUNT = 4;

void help() {
    std::cout << "Usage: \n";
    std::cout << "Create node: create id [parent]\n";
    std::cout << "Get sum of n numbers: exec id n k1 ... kn\n";
    std::cout << "Check node availability: heartbit [time]";
    std::cout << std::endl;
}

void send_msg_to_children(ControlNode& node, Message& msg) {
    for (auto& child : node.children()) {
        msg.send(*child, zmq::send_flags::dontwait);
    }
}

std::string get_children_msg(ControlNode& node) {
    std::string msgs = "";
    for (auto child : node.children()) {
        Message msg;
        msg.receive(*child, zmq::recv_flags::dontwait);
        msgs += msg.data() + ' ';
    }
    return msgs;
}

void flush_socket(zmq::socket_t& socket) {
    Message msg;
    msg.receive(socket, zmq::recv_flags::dontwait);
    while (msg.type() != MessageType::empty) {
        msg.receive(socket, zmq::recv_flags::dontwait);
    }
}

void do_heartbit(ControlNode& node) {
    int delay;
    std::cin >> delay;
    for (auto child : node.children()) {
        flush_socket(*child);
    }
    Message request(MessageType::heartbit, std::to_string(delay) + ' ' + std::to_string(ATTEMPT_HEARTBIT_COUNT));
    send_msg_to_children(node, request);
    std::unordered_set<int> unavailable_node_ids = node.existing_ids();
    unavailable_node_ids.erase(-1);
    auto start = std::chrono::high_resolution_clock::now();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    while (duration.count() < (ATTEMPT_HEARTBIT_COUNT * delay)) {
        std::istringstream buffer(get_children_msg(node));
        int id;
        while (buffer >> id) {
            unavailable_node_ids.erase(id);
        }
        stop = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    }
    if (unavailable_node_ids.size() == 0) {
        std::cout << "Ok" << std::endl;
    } else {
        for (int id : unavailable_node_ids) {
            std::cout << "Heartbit: node " << id << " is unavailable now" << std::endl;
        }
    }
}

void routine(ControlNode& node) {
    while (true) {
        std::string cmd;
        std::cin >> cmd;
        if (cmd == "create") {
            int id, parent;
            std::cin >> id >> parent;
            try {
                std::cout << "Ok: " << node.new_node(id, parent) << std::endl;
            } catch (std::exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        } else if (cmd == "exec") {
            int id;
            std::cin >> id;
            if (node.existing_ids().find(id) == node.existing_ids().end()) {
                std::cout << "Can't find the child" << std::endl;
                continue;
            }
            std::string exec_data;
            std::getline(std::cin, exec_data);
            Message request(MessageType::exec, std::to_string(id) + ' ' + exec_data);
            send_msg_to_children(node, request);
        } else if (cmd == "help") {
            help();
        } else if (cmd == "heartbit") {
            do_heartbit(node);
        } else if (cmd == "q") {
            Message request(MessageType::shutdown, "");
            send_msg_to_children(node, request);
            exit(0);
        } else {
            std::cout << "Wrong command!" << std::endl;
        }
    }
}

int main() {
    ControlNode node;
    std::cout << "Control node started. Base port is " << node.base_port() << std::endl;
    routine(node);

    return 0;
}
