#ifndef SISOP2_SAVEFILEHANDLER_H
#define SISOP2_SAVEFILEHANDLER_H


#include <infra/messaging/Message.h>
#include <application/UserService.h>
#include <infra/messaging/MessageStreamer.h>
#include <infra/messaging/MessageHandler.h>
#include "UploadFileRequest.h"

class SaveFileHandler : public MessageHandler{

    UserService& service;

  public:
    SaveFileHandler(UserService& service) : service(service){};
    void handle(Message message, MessageStreamer& messageStreamer) override;
    void handle(UploadFileRequest request);
};


#endif
