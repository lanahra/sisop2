#ifndef LIST_FILE_ENTRIES_HANDLER_H
#define LIST_FILE_ENTRIES_HANDLER_H

#include "application/UserService.h"
#include "infra/messaging/MessageHandler.h"

class ListFileEntriesHandler : public MessageHandler {
    UserService& service;

  public:
    ListFileEntriesHandler(UserService& service) : service(service){};
    void handle(std::string name, MessageStreamer& messageStreamer) override;
};

#endif
