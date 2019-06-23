
#include <list>
#include <stdexcept>
#include <server/ReplicaManagers.h>
#include "infra/messaging/MessageHandler.h"
#include "infra/messaging/Message.h"
#include "infra/messaging/MessageStreamer.h"
#include "UploadFileRequest.h"

class IpClientHandler : public MessageHandler {
    //std::list<std::string>& clientList;
    ReplicaManagers& replicaManagers;



  public:
    IpClientHandler(ReplicaManagers& replicaManagers) :
                    replicaManagers(replicaManagers){};
    void handle(Message message, MessageStreamer& messageStreamer) override;

};
