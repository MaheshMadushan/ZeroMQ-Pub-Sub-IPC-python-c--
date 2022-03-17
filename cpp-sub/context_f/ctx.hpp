#ifndef CTX_HPP
#define CTX_HPP

// under construction
#define PYCPPIPC_DELETE(p_object)          \
    {                                      \
        delete p_object;                   \
        p_object = 0;                      \
    }

#include <zmq.hpp>

class ctx
{
    private:
        zmq::context_t *context;
    public:
        ctx(/* args */);
        ~ctx();
};

ctx::ctx(/* args */)
{
    
}

ctx::~ctx()
{
}


#endif