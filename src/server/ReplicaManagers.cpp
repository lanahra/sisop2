#include <infra/messaging/SocketMessageStreamer.h>
#include "server/ReplicaManagers.h"

void ReplicaManagers::broadcast(Message message) {
    for(std::shared_ptr<Socket> socket : sockets){
        auto messageStreamer = std::make_shared<SocketMessageStreamer>(socket);
        messageStreamer->send(message);
    }
}

void ReplicaManagers::addBackupServerDescription(std::string address, int port){
    struct ServerDescription newServerDescription;
    newServerDescription.address = address;
    newServerDescription.port = port;
    backupsDescriptions.push_back(newServerDescription);
}

