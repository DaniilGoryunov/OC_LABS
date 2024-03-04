#pragma once

#include "zmq.hpp"
#include <string>
#include <sstream>

namespace lab {
    enum MessageType {
        exec,
        heartbit,
        bind_node,
        heartbit_result,
        error,
        shutdown,
        empty
    };

    class Message {
    private:
        MessageType _type;
        std::string _data;
    public:
        Message() = default;
        Message(MessageType type, const std::string& data);
        ~Message() = default;
        void receive(zmq::socket_t& socket, zmq::recv_flags flags = zmq::recv_flags::none);
        void send(zmq::socket_t& socket, zmq::send_flags flags = zmq::send_flags::none) const;
        MessageType type() const;
        const std::string& data() const;
    private:
        void _msg_to_string(const zmq::message_t& msg, std::string& str);
    };
};
