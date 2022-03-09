#include <iostream>
#include <zmq.hpp>
#include <zmq_addon.hpp>
#include <thread>

void subcribe(char channel[])
{

    zmq::context_t ctx;
    zmq::socket_t subscriber(ctx,zmq::socket_type::sub);
    subscriber.connect("tcp://localhost:6001");
    zmq_setsockopt (subscriber, ZMQ_SUBSCRIBE, channel, 1);

    while (1) {
        
        std::vector<zmq::message_t> recv_msgs;
        zmq::message_t message;
        bool rc = subscriber.recv(&message,1);
        rc && std::cout << message.to_string() << std::endl;
        
    }
}
int main()
{
    char a[] = "A";
    char b[] = "B";
    char c[] = "C";
    std::thread subscriber_a (subcribe,a); // spawn new sub thread
    std::thread subscriber_b (subcribe,b); // spawn new sub thread
    std::thread subscriber_c (subcribe,c); // spawn new sub thread
    subscriber_a.join();
    subscriber_b.join();
    subscriber_c.join();
}