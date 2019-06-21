#include "infra/messaging/TcpSocket.h"
#include "infra/messaging/SocketException.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>

TcpSocket::TcpSocket() {
    socket_ = socket(AF_INET, SOCK_STREAM, 0);
}

TcpSocket::TcpSocket(int socket_) : socket_(socket_){};

TcpSocket::~TcpSocket() {
    close();
}

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
    if (::connect(socket_, (struct sockaddr*)&address, sizeof(address)) != 0) {
        throw SocketException(std::strerror(errno));
    }
}

struct sockaddr_in TcpSocket::addressFrom(std::string host, int port) {
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(host.c_str());
    address.sin_port = htons(port);
    return address;
}

int TcpSocket::readInt() {
    int n;
    read((void*)&n, sizeof(n));
    return ntohl(n);
}

std::string TcpSocket::read(int length) {
    std::string output(length, 0);
    read(&output[0], length);
    return output;
}

void TcpSocket::read(void* buffer, int length) {
    int totalRead = 0;
    int bytesRead;
    while (totalRead < length) {
        bytesRead
            = ::read(socket_, (char*)buffer + totalRead, length - totalRead);
        if (bytesRead <= 0) {
            throw SocketException(std::strerror(errno));
        }
        totalRead += bytesRead;
    }
}

void TcpSocket::writeInt(int n) {
    int w = htonl(n);
    write((void*)&w, sizeof(n));
}

void TcpSocket::write(std::string s) {
    write(&s[0], s.size());
}

void TcpSocket::write(void* buffer, int length) {
    int totalWritten = 0;
    int bytesWritten;
    while (totalWritten < length) {
        bytesWritten = ::write(
            socket_, (char*)buffer + totalWritten, length - totalWritten);
        if (bytesWritten <= 0) {
            throw SocketException(std::strerror(errno));
        }
        totalWritten += bytesWritten;
    }
}

void TcpSocket::close() {
    ::close(socket_);
}

void TcpSocket::select(int timeout) {
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(socket_, &readfds);

    struct timeval tv;
    tv.tv_sec = timeout;
    tv.tv_usec = 0;

    int fds = ::select(socket_ + 1, &readfds, 0, 0, &tv);

    if (fds < 0) {
        throw SocketException(std::strerror(errno));
    } else if (fds == 0) {
        throw SocketException("Socket select timed out");
    }
}
