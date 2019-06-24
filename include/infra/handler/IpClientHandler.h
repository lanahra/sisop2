
#include <vector>
#include <stdexcept>
#include <server/ReplicaManagers.h>
#include "infra/messaging/MessageHandler.h"
#include "infra/messaging/Message.h"
#include "infra/messaging/MessageStreamer.h"
#include "UploadFileRequest.h"

class IpClientHandler : public MessageHandler {
    std::vector<std::string>& clientList;

    ReplicaManagers& replicaManagers;



  public:
    IpClientHandler(ReplicaManagers& replicaManagers, std::vector<std::string>& clientList) :
                    replicaManagers(replicaManagers), clientList(clientList){};
    void handle(Message message, MessageStreamer& messageStreamer) override;

};
