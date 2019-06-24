#include "server/ReplicaManagers.h"
#include <infra/messaging/SocketMessageStreamer.h>
#include <sstream>

void ReplicaManagers::broadcast(Message message) {
    for (std::shared_ptr<Socket> socket : sockets) {
        SocketMessageStreamer messageStreamer(socket);
        messageStreamer.send(message);
    }
}

void ReplicaManagers::addBackupServerDescription(std::string address,
                                                 int port) {
    struct ServerDescription newServerDescription;
    newServerDescription.address = address;
    newServerDescription.port = port;
    backupsDescriptions.push_back(newServerDescription);
}

void ReplicaManagers::broadcastNewBackupsList() {
    UpdateBackupsListRequest request(backupsDescriptions);
    std::stringstream serialized;
    serialized << request;
    Message updateBackupsListMessage("backup.servers.update", serialized.str());
    broadcast(updateBackupsListMessage);
}
