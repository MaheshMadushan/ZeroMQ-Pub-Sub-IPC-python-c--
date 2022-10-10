#ifndef CTX_HPP
#define CTX_HPP

#include <utilities/utilities.h>
#include <zmq.hpp>
#include <iostream>

namespace IPCCTX
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
            zmq::context_t *_p_context = ZMQ_NULLPTR;
            ctx();

        public:
            static ctx *singleton_ctx;
            static ctx *getCtx();
            void setCtxOption(ctxoption option, int option_value);
            int getCtxOption(ctxoption option);
            ~ctx();
    };
}

IPCCTX::ctx::ctx()
{
    try
    {
        _p_context  = new zmq::context_t();
    }
    catch (const std::bad_alloc &e)
    {
        std::cerr << e.what() /*  std::bad_alloc  */ << '\n';
    }
}

void IPCCTX::ctx::setCtxOption(ctxoption option, int option_value)
{
    this->_p_context->set(static_cast<zmq::ctxopt>(option),option_value);
}

int IPCCTX::ctx::getCtxOption(ctxoption option)
{
    int option_value = this->_p_context->get(static_cast<zmq::ctxopt>(option));
    return option_value;
}

IPCCTX::ctx *IPCCTX::ctx::getCtx()
{
    try
    {
        if(singleton_ctx == ZMQ_NULLPTR){
            singleton_ctx = new ctx();
        }
        return singleton_ctx;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

IPCCTX::ctx::~ctx()
{
    this->_p_context->~context_t();
    IPC_DELETE(_p_context);
}

#endif