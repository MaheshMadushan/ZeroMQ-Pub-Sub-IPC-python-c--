#ifndef CTX_HPP
#define CTX_HPP

#include <zmq.hpp>
#include <iostream>

namespace IPCPYCPPZMQ
{
#ifdef ZMQ_CPP11
    enum class ctxoptions
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
#endif
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

// under construction
#define IPCPYCPPZMQ_DELETE(p_object)        \
    {                                       \
        if(p_object == ZMQ_NULLPTR){        \
            return;                         \
        }                                   \
        delete p_object;                    \
        p_object = 0;                       \
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