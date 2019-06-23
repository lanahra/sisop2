#ifndef SISOP2_REPLICAMANAGERS_H
#define SISOP2_REPLICAMANAGERS_H


#include <infra/messaging/Socket.h>
#include <list>
#include <infra/messaging/Message.h>
#include <server/ServerDescription.h>
#include <infra/handler/UpdateBackupsListRequest.h>

class ReplicaManagers {
    bool isPrimary;
    std::list<std::shared_ptr<Socket>> sockets;
    std::list<ServerDescription> backupsDescriptions;

  public:
    ReplicaManagers() : isPrimary(false), sockets(), backupsDescriptions(){};
    ReplicaManagers(bool isPrimary): isPrimary(isPrimary), sockets(), backupsDescriptions(){};

    void addSocket(std::shared_ptr<Socket> socket){if(isPrimary)sockets.push_back(socket);};
    void addBackupServerDescription(std::string address, int port);
    std::list<std::shared_ptr<Socket>> getSockets(){return sockets;};
    std::list<ServerDescription> getBackupsDescriptions(){return backupsDescriptions;};
    void setBackupsDescriptions(std::list<ServerDescription> newBackupsDescriptions){backupsDescriptions = newBackupsDescriptions;};
    void broadcast(Message message);
    void broadcastNewBackupsList();
};

#endif