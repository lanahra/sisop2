#ifndef TCP_SOCKET_H
#define TCP_SOCKET_H

#include <functional>
#include <memory>
#include "Socket.h"

class TcpSocket : public Socket {
    const int MAX_BACKLOG = 5;

    int socket_;

    struct sockaddr_in addressFrom(int port);
    struct sockaddr_in addressFrom(std::string host, int port);

  public:
    TcpSocket();
    TcpSocket(int socket_);
    void listen(int port) override;
    std::shared_ptr<Socket> accept() override;
    void connect(std::string host, int port) override;
};

#endif
