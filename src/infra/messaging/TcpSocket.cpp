#include "infra/messaging/TcpSocket.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

TcpSocket::TcpSocket() {
    socket_ = socket(AF_INET, SOCK_STREAM, 0);
}

TcpSocket::TcpSocket(int socket_) : socket_(socket_){};

void TcpSocket::listen(int port) {
    struct sockaddr_in address = addressFrom(port);
    bind(socket_, (struct sockaddr*)&address, sizeof(address));
    ::listen(socket_, MAX_BACKLOG);
}

struct sockaddr_in TcpSocket::addressFrom(int port) {
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    return address;
}

std::shared_ptr<Socket> TcpSocket::accept() {
    int inSocket = ::accept(socket_, 0, 0);
    return std::make_shared<TcpSocket>(inSocket);
}

void TcpSocket::connect(std::string host, int port) {
    struct sockaddr_in address = addressFrom(host, port);
    ::connect(socket_, (struct sockaddr*)&address, sizeof(address));
}

struct sockaddr_in TcpSocket::addressFrom(std::string host, int port) {
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(host.c_str());
    address.sin_port = htons(port);
    return address;
}
