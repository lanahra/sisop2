#include "infra/messaging/SecondarySocket.h"

#include <iostream>
#include <thread>
#include "infra/messaging/SocketException.h"

SecondarySocket::~SecondarySocket() {
    close();
}

void SecondarySocket::listen(int port) {
    socket->listen(port);
}

std::shared_ptr<Socket> SecondarySocket::accept() {
    return socket->accept();
}

void SecondarySocket::connect(std::string host, int port) {
    socket->connect(host, port);
}

int SecondarySocket::readInt() {
    while (true) {
        try {
            return socket->readInt();
        } catch (const SocketException& e) {
            handleLostConnection();
        }
    }
}

std::string SecondarySocket::read(int length) {
    while (true) {
        try {
            return socket->read(length);
        } catch (const SocketException& e) {
            handleLostConnection();
        }
    }
}

void SecondarySocket::writeInt(int n) {
    while (true) {
        try {
            socket->writeInt(n);
            break;
        } catch (const SocketException& e) {
            handleLostConnection();
        }
    }
}

void SecondarySocket::write(std::string s) {
    while (true) {
        try {
            socket->write(s);
            break;
        } catch (const SocketException& e) {
            handleLostConnection();
        }
    }
}

void SecondarySocket::handleLostConnection() {
    if (isElected()) {
        assumePrimary();
    } else {
        waitForReconnection();
    }
}

bool SecondarySocket::isElected() {
    std::unique_lock<std::mutex> lk(assumePrimaryMutex);
    if (elected) {
        return true;
    } else {
        elected = replicaManagers.isElected(self);
        return elected;
    }
}

void SecondarySocket::assumePrimary() {
    std::unique_lock<std::mutex> lk(assumePrimaryMutex);
    if (assume) {
        assume = false;

        replicaManagers.elect();

        for (ServerDescription server :
             replicaManagers.getBackupsDescriptions()) {
            auto socket = std::make_shared<TcpSocket>();
            replicaManagers.addSocket(socket);
            socket->connect(server.address, server.port);
            auto listener = factory.listenerFor(socket);
            listener->listen();
        }

        replicaManagers.broadcastNewBackupsList();

        std::thread t([&] { connectionListener.listen(self.port); });
        t.detach();
    }

    throw AssumePrimaryException();
}

void SecondarySocket::waitForReconnection() {
    if (reconnectionMutex.try_lock()) {
        std::cout << "Waiting for reconnection..." << std::endl;
        TcpSocket reconnectionSocket;
        reconnectionSocket.listen(self.port);
        try {
            reconnectionSocket.select(timeout);
        } catch (const SocketException& e) {
            std::clog << e.what() << std::endl;
            std::clog.flush();
            exit(EXIT_FAILURE);
        }
        socket = reconnectionSocket.accept();
        reconnectionSocket.close();
        reconnectionMutex.unlock();
    } else {
        std::this_thread::sleep_for(std::chrono::seconds(timeout));
    }
}
void SecondarySocket::close() {
    socket->close();
}
