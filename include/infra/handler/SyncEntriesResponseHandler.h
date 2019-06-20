#ifndef SYNC_ENTRIES_RESPONSE_HANDLER_H
#define SYNC_ENTRIES_RESPONSE_HANDLER_H

#include "ListFileEntriesResponse.h"
#include "SyncEndpoints.h"
#include "application/UserService.h"
#include "infra/messaging/MessageHandler.h"

class SyncEntriesResponseHandler : public MessageHandler {
    SyncEndpoints endpoints;
    UserService& service;

    ListFileEntriesResponse deserializeMessage(std::string body);
    std::list<Message> messagesFor(std::string username, std::list<SyncOperation> operations);
    Message downloadMessageFor(std::string username, std::string filename);
    Message deleteMessageFor(std::string username, std::string filename);
    void sendMessages(std::list<Message> messages,
                      MessageStreamer& messageStreamer);

  public:
    SyncEntriesResponseHandler(SyncEndpoints endpoints,
                               UserService& service)
        : endpoints(endpoints), service(service){};
    void handle(Message message, MessageStreamer& messageStreamer) override;
    Message uploadMessageFor(std::string username, std::string filename);
};

#endif