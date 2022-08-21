#include <gtest/gtest.h>

#include <gabe/networking/utils/Communication.hpp>

typedef gabe::networking::utils::Communication Comm;

// Important objects for the tests
static std::string envelope_topic = "communication_tests";
static zmq::context_t context(1);
static zmq::socket_t publisher(context, zmq::socket_type::pub);
static zmq::socket_t subscriber(context, zmq::socket_type::sub);

TEST(Methodologies, set_identity) {
    std::string pub_id = "publisher_tester";
    std::string sub_id = "subscriber_tester";

    Comm::set_identity(publisher, pub_id);
    Comm::set_identity(subscriber, sub_id);

    ASSERT_TRUE( publisher.get(zmq::sockopt::routing_id) == pub_id );
    ASSERT_TRUE( subscriber.get(zmq::sockopt::routing_id) == sub_id );
}

TEST(Methodologies, send_and_receive) {
    std::string message = envelope_topic + " Testing send method.";

    Comm::send(publisher, message);

    std::string full_content = Comm::receive(subscriber);
    
    ASSERT_TRUE( full_content == message );
}

TEST(Methodologies, sendmore_and_receive) {
    std::string message = "Testing send method.";

    Comm::send_more(publisher, envelope_topic);
    Comm::send(publisher, message);

    std::string envelope = Comm::receive(subscriber);
    std::string content = Comm::receive(subscriber);
    
    ASSERT_TRUE( envelope == envelope_topic );
    ASSERT_TRUE( content == message );
}

TEST(Methodologies, send_and_receivemore) {
    std::string message = envelope_topic + " Testing send method.";

    Comm::send(publisher, message);

    std::string full_content = Comm::receive(subscriber);
    bool more_to_receive = Comm::receive_more(subscriber);
    
    ASSERT_TRUE( full_content == message );
    ASSERT_TRUE( more_to_receive == false );
}

TEST(Methodologies, sendmore_and_receivemore) {
    std::string message = "Testing send method.";

    Comm::send_more(publisher, envelope_topic);
    Comm::send(publisher, message);

    std::string envelope = Comm::receive(subscriber);
    bool after_receiving_envelope = Comm::receive_more(subscriber);
    std::string content = Comm::receive(subscriber);
    bool after_receiving_contents = Comm::receive_more(subscriber);
    
    ASSERT_TRUE( envelope == envelope_topic );
    ASSERT_TRUE( content == message );
    ASSERT_TRUE( after_receiving_envelope == true );
    ASSERT_TRUE( after_receiving_contents == false );
}



int main(int argc, char **argv) {
    // Prepares the objects that will be used in all the tests
    publisher.bind("tcp://127.0.0.1:5555");
    subscriber.connect("tcp://127.0.0.1:5555");
    subscriber.set(zmq::sockopt::subscribe, envelope_topic);

    // Just to make sure the sockets are ready
    zmq_sleep(1);

    // Executes the tests
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
