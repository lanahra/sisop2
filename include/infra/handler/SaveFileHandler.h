#ifndef SAVE_FILE_HANDLER_H
#define SAVE_FILE_HANDLER_H

#include <server/ReplicaManagers.h>
#include "infra/messaging/MessageHandler.h"
#include "application/UserService.h"
#include "infra/messaging/Message.h"
#include "infra/messaging/MessageStreamer.h"
#include "UploadFileRequest.h"

class SaveFileHandler : public MessageHandler {
    UserService& service;
    ReplicaManagers& replicaManagers;

    void handle(UploadFileRequest request);

  public:
    SaveFileHandler(UserService& service, ReplicaManagers& replicaManagers) :
                    service(service), replicaManagers(replicaManagers){};
    void handle(Message message, MessageStreamer& messageStreamer) override;
};

#endif
