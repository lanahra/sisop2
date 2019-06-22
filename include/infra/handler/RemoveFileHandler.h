#ifndef REMOVE_FILE_HANDLER_H
#define REMOVE_FILE_HANDLER_H

#include <server/ReplicaManagers.h>
#include "RemoveFileRequest.h"
#include "application/UserService.h"
#include "infra/messaging/MessageHandler.h"

class RemoveFileHandler : public MessageHandler {
    UserService& service;
    ReplicaManagers& replicaManagers;

    void handle(RemoveFileRequest request);

  public:
    RemoveFileHandler(UserService& service, ReplicaManagers& replicaManagers) :
                        service(service), replicaManagers(replicaManagers){};
    void handle(Message message, MessageStreamer& socket) override;
};

#endif