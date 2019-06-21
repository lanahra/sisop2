#include <infra/messaging/SocketMessageStreamer.h>
#include "server/ReplicaManagers.h"

void ReplicaManagers::broadcast(Message message) {
    for(std::shared_ptr<Socket> socket : sockets){
        auto messageStreamer = std::make_shared<SocketMessageStreamer>(socket);
        messageStreamer->send(message);
    }
}