// encapsulate message
// encapsulate all processes realated to message
// user only need to specify message that in the intsererst of theirs

#include <zmq.hpp>
class message_f
{
    private:
        zmq::message_t message  = nullptr;
    public:
        message_f();
        ~message_f();
};

message_f::message_f(/* args */)
{
    zmq::message_t 
}

message_f::~message_f()
{
}
