#ifndef DOWNLOAD_FILE_RESPONSE_HANDLER_H
#define DOWNLOAD_FILE_RESPONSE_HANDLER_H

#include <ostream>
#include "DownloadFileResponse.h"
#include "application/UserService.h"
#include "infra/messaging/MessageHandler.h"

class DownloadFileResponseHandler : public MessageHandler {
    const std::string ERROR_MESSAGE = "file not found\n";

    UserService& service;
    std::ostream& output;

    DownloadFileResponse deserializeMessage(std::string body);

  public:
    DownloadFileResponseHandler(UserService& service, std::ostream& output)
        : service(service), output(output){};
    void handle(Message message, MessageStreamer& messageStreamer) override;
};

#endif