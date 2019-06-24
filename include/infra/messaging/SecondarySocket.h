#ifndef SISOP2_SECONDARYSOCKET_H
#define SISOP2_SECONDARYSOCKET_H

#include <server/ReplicaManagers.h>
#include <mutex>
#include "AsyncMessageListenerFactory.h"
#include "ConnectionListener.h"
#include "Socket.h"
#include "TcpSocket.h"
#include "server/ServerDescription.h"

class SecondarySocket : public Socket {
    std::shared_ptr<Socket> socket;
    ServerDescription self;
    int timeout;
    std::mutex reconnectionMutex;
    std::mutex assumePrimaryMutex;
    ReplicaManagers& replicaManagers;
    bool assume;
    bool elected;
    AsyncMessageListenerFactory& factory;
    ConnectionListener& connectionListener;
    std::list<std::string>& clients;

    bool isElected();
    void assumePrimary();
    void handleLostConnection();
    void waitForReconnection();

  public:
    SecondarySocket(ServerDescription self,
                    int timeout,
                    ReplicaManagers& replicaManagers,
                    AsyncMessageListenerFactory& factory,
                    ConnectionListener& connectionListener,
                    std::list<std::string>& clients)
        : socket(std::make_shared<TcpSocket>()),
          self(self),
          timeout(timeout),
          replicaManagers(replicaManagers),
          assume(true),
          elected(false),
          factory(factory),
          connectionListener(connectionListener),
          clients(clients){};
    ~SecondarySocket();
    void listen(int port) override;
    std::shared_ptr<Socket> accept() override;
    void connect(std::string host, int port) override;
    int readInt() override;
    std::string read(int length) override;
    void writeInt(int n) override;
    void write(std::string s) override;
    void close() override;
};

class AssumePrimaryException : public std::runtime_error {
  public:
    AssumePrimaryException() : std::runtime_error("Assuming primary"){};
};

#endif