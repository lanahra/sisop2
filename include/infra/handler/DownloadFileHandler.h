#ifndef DOWNLOAD_FILE_HANDLER_H
#define DOWNLOAD_FILE_HANDLER_H

#include "DownloadFileRequest.h"
#include "DownloadFileResponse.h"
#include "application/UserService.h"
#include "infra/messaging/MessageHandler.h"

class DownloadFileHandler : public MessageHandler {
    UserService& service;

    DownloadFileResponse handle(DownloadFileRequest request);
    File tryToGetFile(DownloadFileRequest request);

  public:
    DownloadFileHandler(UserService& service) : service(service){};
    void handle(Message message, MessageStreamer& messageStreamer) override;
    DownloadFileRequest deserializeRequest(std::string body);
    std::string serializeResponse(DownloadFileResponse response);
};

#endif
