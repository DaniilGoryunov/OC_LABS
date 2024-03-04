#include "calculating_node.h"

using namespace lab;

CalculatingNode::CalculatingNode(int base_port, int id) : _base_port{base_port}, _id{id}, _parent{_ctx, zmq::socket_type::pair} {
    _parent.connect("tcp://localhost:" + std::to_string(_base_port + _id));
    _parent.set(zmq::sockopt::rcvtimeo, 200);
}

std::vector<zmq::socket_t*>& CalculatingNode::children() {
    return _children;
}

zmq::socket_t* CalculatingNode::parent() {
    return &_parent;
}

int CalculatingNode::id() const {
    return _id;
}

int CalculatingNode::exec(const std::vector<int>& nums) const {
    int sum = 0;
    for (int num : nums) {
        sum += num;
    }
    return sum;
}

void CalculatingNode::connect_child(int child_id) {
    zmq::socket_t* child = new zmq::socket_t(_ctx, zmq::socket_type::pair);
    (*child).bind("tcp://*:" + std::to_string(_base_port + child_id));
    (*child).set(zmq::sockopt::rcvtimeo, 1000);
    _children.push_back(child);
}
