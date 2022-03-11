#include <iostream>
#include <zmq.hpp>
#include <zmq_addon.hpp>
#include <thread>
#include <signal.h> // POSIX

#ifdef _WIN32
    #include <Windows.h>
#else
    #include <unistd.h>
#endif

// under construction
#define PYCPPIPC_DELETE(p_object)          \
    {                                      \
        delete p_object;                   \
        p_object = 0;                      \
    }

struct context
{
    zmq::context_t *ctx; // socket context
    const char *channel_name;
    const char *server_addr;
};

void interrupt_handler(int sig_num){
    std::cout << "process intterupted" << std::endl;
    signal(SIGINT,SIG_DFL); // dflt action reregsitering
}

void subcribe(context ctx)
{
    zmq::context_t *context = ctx.ctx;
    zmq::socket_t subscriber(*context,zmq::socket_type::sub);
    subscriber.connect(ctx.server_addr);
    size_t channel_name_size = sizeof(*ctx.channel_name)/sizeof(ctx.channel_name[0]);
    zmq_setsockopt (subscriber, ZMQ_SUBSCRIBE,  ctx.channel_name, channel_name_size);

    while (1) {
        
        std::vector<zmq::message_t> recv_msgs;
        zmq::message_t message;
        bool rc = subscriber.recv(&message,1);
        rc && std::cout << message.to_string() << std::endl; // if recicved print msg
        
    }
}

int main()
{

    context a_context;
    a_context.server_addr = "tcp://localhost:6001";
    a_context.ctx = new zmq::context_t();
    a_context.channel_name  = "A";

    std::thread subscriber_a (subcribe,a_context); // spawn new sub thread

    context b_context;
    b_context.server_addr = "tcp://localhost:6001";
    b_context.ctx = a_context.ctx; // use a's context
    b_context.channel_name = "B";

    std::thread subscriber_b (subcribe,b_context); // spawn new sub thread

    context c_context;
    c_context.server_addr = "tcp://localhost:6001";
    c_context.ctx = new zmq::context_t(); // use new context
    c_context.channel_name = "D";
    
    std::thread subscriber_c (subcribe,c_context); // spawn new sub thread
    signal(SIGINT,interrupt_handler);

    sleep(10);

    subscriber_a.join();
    subscriber_b.join();
    subscriber_c.join();

}