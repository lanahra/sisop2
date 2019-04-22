#ifndef REMOVE_FILE_HANDLER_H
#define REMOVE_FILE_HANDLER_H

#include "RemoveFileRequest.h"
#include "application/UserService.h"
#include "infra/messaging/MessageHandler.h"

class RemoveFileHandler : public MessageHandler {
    UserService& service;

    void handle(RemoveFileRequest request);

  public:
    RemoveFileHandler(UserService& service) : service(service){};
    void handle(Message message, MessageStreamer& socket) override;
};

#endif