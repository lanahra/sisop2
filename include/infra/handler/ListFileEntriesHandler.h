#ifndef LIST_FILE_ENTRIES_HANDLER_H
#define LIST_FILE_ENTRIES_HANDLER_H

#include "application/UserService.h"
#include "infra/messaging/MessageHandler.h"

class ListFileEntriesHandler : public MessageHandler {
    UserService& service;

  public:
    ListFileEntriesHandler(UserService& service) : service(service){};
    void handle(Message message, MessageStreamer& messageStreamer) override;
};

#endif
