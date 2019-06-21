#include "infra/messaging/ReconnectableTcpSocket.h"
#include "infra/messaging/SocketException.h"
#include "infra/messaging/TcpSocket.h"
#include <iostream>

ReconnectableTcpSocket::ReconnectableTcpSocket(int reconnectionPort,
                                               int reconnectionTimeout)
    : socket(std::make_shared<TcpSocket>()),
      reconnectionPort(reconnectionPort),
      reconnectionTimeout(reconnectionTimeout) {
}

ReconnectableTcpSocket::~ReconnectableTcpSocket() {
    close();
}

void ReconnectableTcpSocket::listen(int port) {
    socket->listen(port);
}

std::shared_ptr<Socket> ReconnectableTcpSocket::accept() {
    return socket->accept();
}

void ReconnectableTcpSocket::connect(std::string host, int port) {
    socket->connect(host, port);
}

int ReconnectableTcpSocket::readInt() {
    while (true) {
        try {
            return socket->readInt();
        } catch (const SocketException& e) {
            waitForReconnection();
        }
    }
}

std::string ReconnectableTcpSocket::read(int length) {
    while (true) {
        try {
            return socket->read(length);
        } catch (const SocketException& e) {
            waitForReconnection();
        }
    }
}

void ReconnectableTcpSocket::writeInt(int n) {
    while (true) {
        try {
            socket->writeInt(n);
            break;
        } catch (const SocketException& e) {
            waitForReconnection();
        }
    }
}

void ReconnectableTcpSocket::write(std::string s) {
    while (true) {
        try {
            socket->write(s);
            break;
        } catch (const SocketException& e) {
            waitForReconnection();
        }
    }
}

void ReconnectableTcpSocket::waitForReconnection() {
    std::cout << "Waiting for reconnection..." << std::endl;
    TcpSocket reconnectionSocket;
    reconnectionSocket.listen(reconnectionPort);
    try {
        reconnectionSocket.select(reconnectionTimeout);
    } catch (const SocketException& e) {
        std::clog << e.what() << std::endl;
        std::clog.flush();
        exit(EXIT_FAILURE);
    }
    socket = reconnectionSocket.accept();
    reconnectionSocket.close();
}

void ReconnectableTcpSocket::close() {
    socket->close();
}
