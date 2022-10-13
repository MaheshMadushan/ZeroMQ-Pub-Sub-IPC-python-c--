#include <socket_f.hpp>


IPCSOCK::sock_f::sock_f(){
    this->socket = new zmq::socket_t();
}

void IPCSOCK::sock_f::bindSocketAddres(std::string const &address){
    this->socket->bind(address);
}

void IPCSOCK::sock_f::connectTo(std::string const &address){
    this->socket->connect(address);
}

void IPCSOCK::sock_f::disconnectFrom(std::string const &address){
    this->socket->disconnect(address);
}

bool IPCSOCK::sock_f::isConnected(){
    return this->socket->connected();
}

void IPCSOCK::sock_f::setSocketOption(int option_,const void *optionValue, size_t optionValueLength){
    this->socket->setsockopt(option_,optionValue,optionValueLength);
}

template <typename T>
T IPCSOCK::sock_f::getSocketOption(int option_){
    return this->socket->getsockopt<T>(option_);
}

IPCSOCK::sock_f::~sock_f()
{
    IPC_DELETE(socket);
}
