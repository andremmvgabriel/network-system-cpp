#pragma once

#include <string>

#include <zmq.hpp>

namespace gabe {
    namespace networking {
        namespace utils {
            class Communication
            {
            public:
                Communication() = delete; // Disables its construction

                static std::string receive(zmq::socket_ref socket, zmq::recv_flags flags = zmq::recv_flags::none);
                static bool receive_more(zmq::socket_ref socket);

                static bool send(zmq::socket_ref socket, const std::string &message, zmq::send_flags flags = zmq::send_flags::none);
                static bool send_more(zmq::socket_ref socket, const std::string &message);

                static void set_identity(zmq::socket_ref socket, const std::string &id);
            };
        }
    }
}
