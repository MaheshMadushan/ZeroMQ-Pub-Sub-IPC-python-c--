// encapsulate message
// encapsulate all processes realated to message
// user only need to specify message that in the intsererst of theirs
// keep follwing dunction in mind. this is in socket.
// send_result_t send(message_t &msg, send_flags flags)
//             {
//                 int nbytes = zmq_msg_send(msg.handle(), _handle, static_cast<int>(flags));
//                 if (nbytes >= 0)
//                     return static_cast<size_t>(nbytes);
//                 if (zmq_errno() == EAGAIN)
//                     return {};
//                 throw error_t();
//             }
#include <zmq.hpp>
#define IPCPYCPPZMQ_DELETE(p_object)  \
    {                                 \
        if(p_object == ZMQ_NULLPTR){  \
            return;                   \
        }                             \
        delete p_object;              \
        p_object = 0;                 \
    }

class message_f
{
    private:
        zmq::message_t *message  = ZMQ_NULLPTR;
        // void * free_data_buffer_fn(void *data, void *hint);
    public:
        message_f(void *data);
        ~message_f();
};


message_f::message_f(void *data)
{
   this->message = new zmq::message_t(data,sizeof(data),free_data_buffer_fn,ZMQ_NULLPTR);
}

message_f::~message_f()
{
    IPCPYCPPZMQ_DELETE(this->message);
}

// free function - shouldn't be a member function - read https://stackoverflow.com/questions/2298242/callback-functions-in-c
void free_data_buffer_fn(void *data, void *hint)
{
    IPCPYCPPZMQ_DELETE(data);
}