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
        void freeBuffer(void *data, void *hint); // ffn ad hint
    public:
        message_f();
        ~message_f();
};
message_f::message_f()
{
   this->message = new zmq::message_t();
}
message_f::~message_f()
{
    IPCPYCPPZMQ_DELETE(this->message);
}
