#ifndef RECONNECTABLE_TCP_SOCKET_H
#define RECONNECTABLE_TCP_SOCKET_H

#include "Socket.h"

class ReconnectableTcpSocket : public Socket {
    std::shared_ptr<Socket> socket;
    int reconnectionPort;
    int reconnectionTimeout;

    void waitForReconnection();

  public:
    ReconnectableTcpSocket(int reconnectionPort, int reconnectionTimeout);
    ~ReconnectableTcpSocket();
    void listen(int port) override;
    std::shared_ptr<Socket> accept() override;
    void connect(std::string host, int port) override;
    int readInt() override;
    std::string read(int length) override;
    void writeInt(int n) override;
    void write(std::string s) override;
    void close() override;
};

#endif