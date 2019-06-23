#ifndef SISOP2_REPLICAMANAGERS_H
#define SISOP2_REPLICAMANAGERS_H


#include <infra/messaging/Socket.h>
#include <list>
#include <infra/messaging/Message.h>
#include <server/ServerDescription.h>

class ReplicaManagers {
    std::list<std::shared_ptr<Socket>> sockets;
    std::list<ServerDescription> backupsDescriptions;

  public:
    ReplicaManagers(): sockets(), backupsDescriptions(){};

    void addSocket(std::shared_ptr<Socket> socket){sockets.push_back(socket);};
    void addBackupServerDescription(std::string address, int port);
    std::list<std::shared_ptr<Socket>> getSockets(){return sockets;};
    std::list<ServerDescription> getBackupsDescriptions(){return backupsDescriptions;};
    void broadcast(Message message);
};

#endif