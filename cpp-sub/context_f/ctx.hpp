#ifndef CTX_HPP
#define CTX_HPP

// under construction
#define PYCPPIPC_DELETE(p_object)           \
    {                                       \
        if(p_object == ZMQ_NULLPTR){        \
            return;                         \
        }                                   \
        delete p_object;                    \
        p_object = 0;                       \
    }

#include <zmq.hpp>

class ctx
{
    private:
        // type name             "new" returns a p
        zmq::context_t *context = ZMQ_NULLPTR;
    public:
        ctx();
        ~ctx();
};

ctx::ctx()
{
    context  = new zmq::context_t();
}

ctx::~ctx()
{
    PYCPPIPC_DELETE(context);
}


#endif