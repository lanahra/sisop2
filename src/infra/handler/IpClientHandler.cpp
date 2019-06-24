#include "infra/handler/IpClientHandler.h"
#include <algorithm>
#include <sstream>

void IpClientHandler::handle(Message message,
                             MessageStreamer& messageStreamer) {
    replicaManagers.broadcast(message);

    std::string clientIp = message.getBody();
    if (std::find(clientList.begin(), clientList.end(), clientIp)
        == clientList.end()) {
        clientList.push_back(clientIp);
    }
}
