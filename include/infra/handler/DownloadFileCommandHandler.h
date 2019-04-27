#ifndef DOWNLOAD_FILE_COMMAND_HANDLER_H
#define DOWNLOAD_FILE_COMMAND_HANDLER_H

#include <ostream>
#include "infra/messaging/CommandHandler.h"

class DownloadFileCommandHandler : public CommandHandler {
    const std::string ERROR_MESSAGE = "download command takes 1 argument\n";

    std::string username;
    std::string operation;
    std::string response;
    std::ostream& output;

    Message commandFrom(std::string filename);

  public:
    DownloadFileCommandHandler(std::string username,
                               std::string operation,
                               std::string response,
                               std::ostream& output)
        : username(username),
          operation(operation),
          response(response),
          output(output){};
    void handle(std::vector<std::string> args,
                MessageStreamer& messageStreamer) override;
};

#endif