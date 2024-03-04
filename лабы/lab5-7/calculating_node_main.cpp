#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <chrono>
#include <thread>
#include "calculating_node.h"

using namespace lab;

void redirect_request(Message& request, CalculatingNode& node) {
    for (auto& child : node.children()) {
        request.send(*child, zmq::send_flags::dontwait);
    }
}

std::string get_msgs_from_children(CalculatingNode& node) {
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

void do_heartbit(Message& request, CalculatingNode& node) {
    for (auto child : node.children()) {
        flush_socket(*child);
    }
    redirect_request(request, node);
    std::istringstream buffer(request.data());
    int delay, attempts;
    buffer >> delay >> attempts;
    for (int i = 0; i < attempts; ++i) {
        std::string children_reply = get_msgs_from_children(node);
        Message reply(MessageType::heartbit_result, children_reply + std::to_string(node.id()));
        reply.send(*node.parent(), zmq::send_flags::dontwait);
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
}

void routine(CalculatingNode& node) {
    while (true) {
        Message request;
        request.receive(*node.parent());
        if (request.type() == MessageType::bind_node) {
            std::istringstream buffer(request.data());
            int parent_id, id;
            buffer >> parent_id >> id;
            if (node.id() == parent_id) {
                node.connect_child(id);
            } else {
                redirect_request(request, node);
            }
        } else if (request.type() == MessageType::exec) {
            std::istringstream buffer(request.data());
            int node_id;
            buffer >> node_id;
            if (node.id() != node_id) {
                redirect_request(request, node);
                continue;
            }
            int n;
            buffer >> n;
            std::vector<int> exec_data(n);
            for (int i = 0; i < n; ++i) {
                buffer >> exec_data[i];
            }
            int result = node.exec(exec_data);
            std::cout << node.id() << "; " << result << std::endl;
        } else if (request.type() == MessageType::shutdown) {
            redirect_request(request, node);
            break;
        } else if (request.type() == MessageType::heartbit) {
            do_heartbit(request, node);
        }
    }
}

int main(int argc, char** argv) {
    if (argc != 3) {
        std::perror("Too few arguments");
        std::exit(1);
    }
    int base_port = std::stoi(argv[1]);
    int id = std::stoi(argv[2]);
    CalculatingNode node(base_port, id);
    routine(node);

    return 0;
}
