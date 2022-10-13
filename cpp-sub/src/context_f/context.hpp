#ifndef CTX_HPP
#define CTX_HPP

#include <utilities/utilities.hpp>
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

    // ctx *IPCCTX::ctx::singleton_ctx;
    
}

#endif