#ifndef LIST_SERVER_ENTRIES_COMMAND_HANDLER_H
#define LIST_SERVER_ENTRIES_COMMAND_HANDLER_H

#include "infra/messaging/CommandHandler.h"

class ListServerEntriesCommandHandler : public CommandHandler {
    std::string username;
    std::string operation;
    std::string response;

  public:
    ListServerEntriesCommandHandler(std::string username,
                                    std::string operation,
                                    std::string response)
        : username(username), operation(operation), response(response){};
    void handle(std::vector<std::string> args,
                MessageStreamer& messageStreamer) override;
};

#endif