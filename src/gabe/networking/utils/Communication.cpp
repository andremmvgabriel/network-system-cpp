#include <gabe/networking/utils/Communication.hpp>

std::string gabe::networking::utils::Communication::receive(zmq::socket_ref socket, zmq::recv_flags flags) {
    zmq::message_t msg;

    zmq::recv_result_t result = socket.recv(msg, flags);

    return std::string( static_cast<char*>(msg.data()), msg.size() );
}

bool gabe::networking::utils::Communication::receive_more(zmq::socket_ref socket) {
    return socket.get(zmq::sockopt::rcvmore);
}

bool gabe::networking::utils::Communication::send(zmq::socket_ref socket, const std::string &message, zmq::send_flags flags) {
    zmq::message_t msg(message.size());

    memcpy(msg.data(), message.data(), message.size());

    return socket.send(msg, flags).has_value();
}

bool gabe::networking::utils::Communication::send_more(zmq::socket_ref socket, const std::string &message) {
    return send(socket, message, zmq::send_flags::sndmore);
}

void gabe::networking::utils::Communication::set_identity(zmq::socket_ref socket, const std::string &id) {
    socket.set( zmq::sockopt::routing_id, id );
}
