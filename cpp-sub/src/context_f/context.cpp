#include <context.hpp>


using namespace IPCCTX;

ctx *ctx::singleton_ctx = ZMQ_NULLPTR;

ctx::ctx()
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

void ctx::setCtxOption(ctxoption option, int option_value)
{
    this->_p_context->set(static_cast<zmq::ctxopt>(option),option_value);
}

int ctx::getCtxOption(ctxoption option)
{
    int option_value = this->_p_context->get(static_cast<zmq::ctxopt>(option));
    return option_value;
}

ctx *ctx::getCtx()
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

ctx::~ctx()
{
    this->_p_context->~context_t();
    IPC_DELETE(_p_context);
}
