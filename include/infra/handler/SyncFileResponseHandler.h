#ifndef SYNC_FILE_RESPONSE_HANDLER_H
#define SYNC_FILE_RESPONSE_HANDLER_H

#include <ostream>
#include "DownloadFileResponse.h"
#include "application/UserService.h"
#include "infra/messaging/MessageHandler.h"

class SyncFileResponseHandler : public MessageHandler {
    std::string username;
    UserService& service;

    DownloadFileResponse deserializeMessage(std::string body);

  public:
    SyncFileResponseHandler(std::string username, UserService& service)
        : username(username), service(service){};
    void handle(Message message, MessageStreamer& messageStreamer) override;
};

#endif