#ifndef CTX_HPP
#define CTX_HPP

#define IPCPYCPPZMQ_DELETE(p_object)  \
    {                                 \
        if(p_object == ZMQ_NULLPTR){  \
            return;                   \
        }                             \
        delete p_object;              \
        p_object = 0;                 \
    }
    
#include <zmq.hpp>
#include <iostream>

namespace IPCPYCPPZMQCTX
{
#ifdef ZMQ_CPP11
    enum class ctxoption
    {
        block_ctx_termination_call = static_cast<int>(zmq::ctxopt::blocky),
        size_of_thread_pool_to_IO_handling = static_cast<int>(zmq::ctxopt::io_threads),
#ifndef _WIN32
        thread_sched_policy = static_cast<int>(zmq::ctxopt::thread_sched_policy),
        thread_priority = static_cast<int>(zmq::ctxopt::thread_priority),
#endif
#ifdef __unix__
        thread_affinity_cpu_add = static_cast<int>(zmq::ctxopt::thread_affinity_cpu_add),
        thread_affinity_cpu_remove = static_cast<int>(zmq::ctxopt::thread_affinity_cpu_remove),
        thread_name_prefix = static_cast<int>(zmq::ctxopt::thread_name_prefix),
#endif
        max_message_size = static_cast<int>(zmq::ctxopt::max_msgsz),
        max_sockets = static_cast<int>(zmq::ctxopt::max_sockets)
    };
#endif

    class ctx
    {
        private:
            // type name             "new" returns a p
            zmq::context_t *context = ZMQ_NULLPTR;
        public:
            ctx();
            void setCtxOption(ctxoption option, int option_value);
            int getCtxOption(ctxoption option);
            ~ctx();
    };
}


IPCPYCPPZMQCTX::ctx::ctx()
{
    try
    {
        context  = new zmq::context_t();
    }
    catch (const std::bad_alloc &e)
    {
        std::cerr << e.what() /*  std::bad_alloc  */ << '\n';
    }
}

void IPCPYCPPZMQCTX::ctx::setCtxOption(ctxoption option, int option_value)
{
    this->context->set(static_cast<zmq::ctxopt>(option),option_value);
}

int IPCPYCPPZMQCTX::ctx::getCtxOption(ctxoption option)
{
    int option_value = this->context->get(static_cast<zmq::ctxopt>(option));
    return option_value;
}

IPCPYCPPZMQCTX::ctx::~ctx()
{
    this->context->~context_t();
    IPCPYCPPZMQ_DELETE(context);
}


#endif