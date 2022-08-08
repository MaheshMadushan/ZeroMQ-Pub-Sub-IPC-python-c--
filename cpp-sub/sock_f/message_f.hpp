// encapsulate message
// encapsulate all processes realated to message
// user only need to specify message that in the intsererst of theirs .keep in mind the follwing function . this is in socket.send_result_t send(message_t &msg, send_flags flags)
//             {
//                 int nbytes = zmq_msg_send(msg.handle(), _handle, static_cast<int>(flags));
//                 if (nbytes >= 0)
//                     return static_cast<size_t>(nbytes);
//                 if (zmq_errno() == EAGAIN)
//                     return {};
//                 throw error_t();
//             }
#include <zmq.hpp>
#include <utilities/utilities.h>

class message_f
{
    private:
        zmq::message_t *message  = ZMQ_NULLPTR;
    
    public:
        message_f(void *data);
        // gets and r-value (no mem address. like num 6 or stirng 'v')
        // Rvalue references allow programmers to avoid logically unnecessary copying 
        // and to provide perfect forwarding functions. 
        message_f(message_f &&rhs) noexcept : message(rhs.message)
        {
            
        };
        ~message_f();
};


message_f::message_f(void *data)
{
    IPC_ASSERT(data != NULL);
    this->message = new zmq::message_t(data,sizeof(data),free_data_buffer_fn,ZMQ_NULLPTR);
}

message_f::~message_f()
{
    IPC_DELETE(this->message);
}

// free function - shouldn't be a member function - read https://stackoverflow.com/questions/2298242/callback-functions-in-c
void free_data_buffer_fn(void *data, void *hint)
{
    IPC_ASSERT(data == NULL);
    IPC_DELETE(data);
}