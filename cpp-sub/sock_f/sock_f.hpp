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
            sock_f(/* args */);
            ~sock_f();
    };
} // namespace IPCPYCPPZMQSOCK

IPCPYCPPZMQSOCK::sock_f::sock_f()
{
    this->socket = new zmq::socket_t();
}
IPCPYCPPZMQSOCK::sock_f::~sock_f()
{
}
#endif