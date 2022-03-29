// encapsulates sockets related methods
// Socket factroy
#ifndef SOCK_H
#define SOCK_H
#include <zmq.hpp>

namespace IPCPYCPPZMQSOCK
{
    class sock_f
    {

        private:
            zmq::socket_t *socket = ZMQ_NULLPTR;

        public:
            sock_f();
            ~sock_f();
            void bindSocketAddres();
            void unbindSocketAddres();
            void connectTo();
            void disconnectFrom();
            bool isConnected();
            void getSocketOption(int option_);
            void setSocketOption(int option_,const void *optionValue, size_t optionValueLength);
    };

} // namespace IPCPYCPPZMQSOCK

IPCPYCPPZMQSOCK::sock_f::sock_f()
{
    this->socket = new zmq::socket_t();
}

IPCPYCPPZMQSOCK::sock_f::~sock_f()
{
    delete socket;
    socket = ZMQ_NULLPTR;
}

#endif