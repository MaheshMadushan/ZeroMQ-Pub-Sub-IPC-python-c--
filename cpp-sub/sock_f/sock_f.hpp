// encapsulates sockets related methods
// Socket factroy
#ifndef SOCK_H
#define SOCK_H

#include <zmq.hpp>

#define INPROC 100
#define TCP 200
#define IPC 300
#define PGM 400
#define EPGM 500

#define IPCPYCPPZMQ_DELETE(p_object)  \
    {                                 \
        if(p_object == ZMQ_NULLPTR){  \
            return;                   \
        }                             \
        delete p_object;              \
        p_object = 0;                 \
    }

namespace IPCPYCPPZMQSOCK
{
    enum socket_types
    {
        in_process_communication = INPROC,
        inter_process_communication = IPC,
        reliable_unicast_tcp = TCP, // disconnected TCP - endpoint don't need to be connected/exists to sen msg
        reliable_pragmatic_general_multicast = PGM,
        udp_pragmatic_encapsulated_general_multicast = EPGM
    };

    class sock_f
    {

        private:
            zmq::socket_t *socket = ZMQ_NULLPTR;

        public:
            sock_f();
            ~sock_f();
            void bindSocketAddres(std::string const &addres);
            void unbindSocketAddres();
            void connectTo(std::string const &address);
            void disconnectFrom(std::string const &address);
            bool isConnected();

            template <typename T>
            T getSocketOption(int option_);

            void setSocketOption(int option_,const void *optionValue, size_t optionValueLength);
    };

} // namespace IPCPYCPPZMQSOCK

IPCPYCPPZMQSOCK::sock_f::sock_f(){
    this->socket = new zmq::socket_t();
}

void IPCPYCPPZMQSOCK::sock_f::bindSocketAddres(std::string const &address){
    this->socket->bind(address);
}

void IPCPYCPPZMQSOCK::sock_f::connectTo(std::string const &address){
    this->socket->connect(address);
}

void IPCPYCPPZMQSOCK::sock_f::disconnectFrom(std::string const &address){
    this->socket->disconnect(address);
}

bool IPCPYCPPZMQSOCK::sock_f::isConnected(){
    return this->socket->connected();
}

void IPCPYCPPZMQSOCK::sock_f::setSocketOption(int option_,const void *optionValue, size_t optionValueLength){
    this->socket->setsockopt(option_,optionValue,optionValueLength);
}

template <typename T>
T IPCPYCPPZMQSOCK::sock_f::getSocketOption(int option_){
    return this->socket->getsockopt<T>(option_);
}

IPCPYCPPZMQSOCK::sock_f::~sock_f()
{
    IPCPYCPPZMQ_DELETE(socket);
}

#endif