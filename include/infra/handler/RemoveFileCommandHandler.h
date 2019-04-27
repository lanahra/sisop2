#ifndef REMOVE_FILE_COMMAND_HANDLER_H
#define REMOVE_FILE_COMMAND_HANDLER_H

#include <ostream>
#include "infra/messaging/CommandHandler.h"

class RemoveFileCommandHandler : public CommandHandler {
    const std::string ERROR_MESSAGE = "delete command takes 1 argument\n";

    std::string username;
    std::string operation;
    std::ostream& output;

  public:
    RemoveFileCommandHandler(std::string username,
                             std::string operation,
                             std::ostream& output)
        : username(username), operation(operation), output(output){};
    void handle(std::vector<std::string> args,
                MessageStreamer& messageStreamer) override;
    Message commandFrom(std::string filename);
};

#endif