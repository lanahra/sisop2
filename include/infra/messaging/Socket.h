#ifndef SOCKET_H
#define SOCKET_H

#include <string>
#include <memory>

class Socket {
  public:
    virtual ~Socket() = default;
    virtual void listen(int port) = 0;
    virtual std::shared_ptr<Socket> accept() = 0;
    virtual void connect(std::string host, int port) = 0;
};

#endif
