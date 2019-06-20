#ifndef SYNC_FILE_RESPONSE_HANDLER_H
#define SYNC_FILE_RESPONSE_HANDLER_H

#include <ostream>
#include "DownloadFileResponse.h"
#include "application/UserService.h"
#include "infra/messaging/MessageHandler.h"

class SyncFileResponseHandler : public MessageHandler {
    UserService& service;

    DownloadFileResponse deserializeMessage(std::string body);

  public:
    SyncFileResponseHandler(UserService& service) : service(service){};
    void handle(Message message, MessageStreamer& messageStreamer) override;
};

#endif