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

#include <utilities/utilities.hpp>

namespace IPCSOCK
{
    enum socket_types
    {
        in_process_communication = INPROC,
        inter_process_communication = IPC,
        reliable_unicast_tcp = TCP, // disconnected TCP - endpoint don't need to be connected/exists to send msg
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

} // namespace IPCSOCK

#endif