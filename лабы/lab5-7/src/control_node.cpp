#include "control_node.h"

using namespace lab;

ControlNode::ControlNode(int base_port) : _base_port{base_port} {
    _existing_ids.insert(-1);
}

std::vector<zmq::socket_t*>& ControlNode::children() {
    return _children;
}

int ControlNode::base_port() const {
    return _base_port;
}

pid_t ControlNode::new_node(int id, int parent_id) {
    const char* exec_path = std::getenv("CALC_NODE_PATH");
    if (exec_path == nullptr) throw std::runtime_error("Can't find calculation node exe");
    if (_existing_ids.find(id) != _existing_ids.end()) throw std::runtime_error("Node with this id already exist");
    if (_existing_ids.find(parent_id) == _existing_ids.end()) throw std::runtime_error("Parent node does not exist");
    _existing_ids.insert(id);
    pid_t pid = fork();
    if (pid == -1) throw std::runtime_error("Fork error");
    if (pid == 0) {
        execl(exec_path, exec_path, std::to_string(_base_port).c_str(), std::to_string(id).c_str(), NULL);
    } else {
        if (parent_id != -1) {
            Message bind_msg(MessageType::bind_node, std::to_string(parent_id) + " " + std::to_string(id));
            for (auto& child : _children) {
                bind_msg.send(*child);
            }
        } else {    // new node connected to control node
            zmq::socket_t* child = new zmq::socket_t(_ctx, zmq::socket_type::pair);
            (*child).bind("tcp://*:" + std::to_string(_base_port + id));
            (*child).set(zmq::sockopt::rcvtimeo, 1000);
            _children.push_back(child);
        }
    }
    return pid;
}

const std::unordered_set<int>& ControlNode::existing_ids() const {
    return _existing_ids;
}
