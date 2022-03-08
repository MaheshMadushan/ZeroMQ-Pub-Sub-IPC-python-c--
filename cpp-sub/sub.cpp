#include <iostream>
#include <zmq.hpp>
#include <zmq_addon.hpp>
int main()
{
    zmq::context_t ctx;
    zmq::socket_t subscriber(ctx, zmq::socket_type::sub);
    subscriber.connect("tcp://localhost:6001");
    zmq_setsockopt (subscriber, ZMQ_SUBSCRIBE, "A", 1);

    while (1) {
        
        std::vector<zmq::message_t> recv_msgs;
        zmq::message_t a;
        subscriber.recv(&a);
        std::cout << a.to_string() << std::endl;
        
    }
    
}