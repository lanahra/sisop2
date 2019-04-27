#ifndef LIST_CLIENT_ENTRIES_COMMAND_HANDLER_H
#define LIST_CLIENT_ENTRIES_COMMAND_HANDLER_H

#include "application/PrinterService.h"
#include "application/UserService.h"
#include "infra/messaging/CommandHandler.h"

class ListClientEntriesCommandHandler : public CommandHandler {
    std::string username;
    UserService& userService;
    PrinterService& printerService;

  public:
    ListClientEntriesCommandHandler(std::string username,
                                    UserService& userService,
                                    PrinterService& printerService)
        : username(username),
          userService(userService),
          printerService(printerService){};
    void handle(std::vector<std::string> args,
                MessageStreamer& messageStreamer) override;
};

#endif