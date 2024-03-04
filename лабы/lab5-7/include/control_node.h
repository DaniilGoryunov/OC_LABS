#pragma once

#include "zmq.hpp"
#include <unistd.h>
#include <vector>
#include <unordered_set>
#include <memory>
#include "message.h"

namespace lab {
    class ControlNode {
    private:
        zmq::context_t _ctx;
        std::vector<zmq::socket_t*> _children;
        std::unordered_set<int> _existing_ids;
        int _base_port;
    public:
        ControlNode(int base_port = 5000);
        ~ControlNode() = default;
        std::vector<zmq::socket_t*>& children();
        const std::unordered_set<int>& existing_ids() const;
        int base_port() const;
        pid_t new_node(int id, int parent_id);
    };
};
