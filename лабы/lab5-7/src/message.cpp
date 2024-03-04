#include "message.h"

using namespace lab;

Message::Message(MessageType type, const std::string& data) : _type{type}, _data{data} {}

void Message::receive(zmq::socket_t& socket, zmq::recv_flags flags) {
    zmq::message_t msg;
    socket.recv(msg, flags);
    std::string msg_str;
    _msg_to_string(msg, msg_str);
    if (msg_str.size() == 0) {
        _type = MessageType::empty;
        return;
    }
    std::istringstream iss(msg_str);
    int type_buf;
    iss >> type_buf;
    std::getline(iss, _data);
    _type = static_cast<MessageType>(type_buf);
}

void Message::send(zmq::socket_t& socket, zmq::send_flags flags) const {
    std::string msg_str = std::to_string(_type);
    msg_str += " " + _data;
    zmq::message_t msg(msg_str);
    socket.send(msg, flags);
}

MessageType Message::type() const {
    return _type;
}

const std::string& Message::data() const {
    return _data;
}

void Message::_msg_to_string(const zmq::message_t& msg, std::string& str) {
    str.resize(msg.size() / sizeof(char));
    std::memcpy(str.data(), msg.data(), msg.size());
}
