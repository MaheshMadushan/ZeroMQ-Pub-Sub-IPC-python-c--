#ifndef CTX_HPP
#define CTX_HPP

// under construction
#define IPCPYCPPZMQ_DELETE(p_object)           \
    {                                       \
        if(p_object == ZMQ_NULLPTR){        \
            return;                         \
        }                                   \
        delete p_object;                    \
        p_object = 0;                       \
    }

#include <zmq.hpp>
#include <iostream>
namespace IPCPYCPPZMQ
{
#ifdef ZMQ_CPP11
    enum class ctxoptions
    {
        
    };
#endif
    class ctx
    {
        private:
            // type name             "new" returns a p
            zmq::context_t *context = ZMQ_NULLPTR;
        public:
            ctx();
            void setCtxOption();
            void getCtxOption();
            ~ctx();
    };
}


IPCPYCPPZMQ::ctx::ctx()
{
    try
    {
        context  = new zmq::context_t();
    }
    catch (const std::bad_alloc &e)
    {
        std::cerr << e.what() /* std::bad_alloc */ << '\n';
    }
}

void IPCPYCPPZMQ::ctx::setCtxOption()
{
    this->context->set(static_cast<zmq::ctxopt>(4),4);
}

IPCPYCPPZMQ::ctx::~ctx()
{
    IPCPYCPPZMQ_DELETE(context);
}


#endif