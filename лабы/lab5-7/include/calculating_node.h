#pragma once

#include "zmq.hpp"
#include <vector>
#include "message.h"

namespace lab {
    class CalculatingNode {
    private:
        zmq::context_t _ctx;
        zmq::socket_t _parent;
        std::vector<zmq::socket_t*> _children;
        int _base_port;
        int _id;
    public:
        CalculatingNode(int base_port, int id);
        ~CalculatingNode() = default;
        std::vector<zmq::socket_t*>& children();
        zmq::socket_t* parent();
        int id() const;
        int exec(const std::vector<int>& nums) const;
        void connect_child(int child_id);
    };
};
