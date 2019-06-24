
#include <server/ReplicaManagers.h>
#include <stdexcept>
#include <list>
#include "UploadFileRequest.h"
#include "infra/messaging/Message.h"
#include "infra/messaging/MessageHandler.h"
#include "infra/messaging/MessageStreamer.h"

class IpClientHandler : public MessageHandler {
    std::list<std::string>& clientList;

    ReplicaManagers& replicaManagers;

  public:
    IpClientHandler(ReplicaManagers& replicaManagers,
                    std::list<std::string>& clientList)
        : replicaManagers(replicaManagers), clientList(clientList){};
    void handle(Message message, MessageStreamer& messageStreamer) override;
};
