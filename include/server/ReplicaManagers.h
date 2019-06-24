#ifndef SISOP2_REPLICAMANAGERS_H
#define SISOP2_REPLICAMANAGERS_H

#include <infra/handler/UpdateBackupsListRequest.h>
#include <infra/messaging/Message.h>
#include <infra/messaging/Socket.h>
#include <server/ServerDescription.h>
#include <list>

class ReplicaManagers {
    std::list<std::shared_ptr<Socket>> sockets;
    std::list<ServerDescription> backupsDescriptions;

  public:
    ReplicaManagers() : sockets(), backupsDescriptions(){};

    void addSocket(std::shared_ptr<Socket> socket) {
        sockets.push_back(socket);
    };

    void addBackupServerDescription(std::string address, int port);

    std::list<std::shared_ptr<Socket>> getSockets() {
        return sockets;
    };

    std::list<ServerDescription> getBackupsDescriptions() {
        return backupsDescriptions;
    };

    void setBackupsDescriptions(
        std::list<ServerDescription> newBackupsDescriptions) {
        backupsDescriptions = newBackupsDescriptions;
    };

    void broadcast(Message message);
    void broadcastNewBackupsList();

    bool isElected(ServerDescription server) {
        return backupsDescriptions.front() == server;
    };

    void elect() {
        backupsDescriptions.remove(backupsDescriptions.front());
    }
};

#endif