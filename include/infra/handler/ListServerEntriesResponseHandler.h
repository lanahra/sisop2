#ifndef LIST_SERVER_ENTRIES_RESPONSE_HANDLER_H
#define LIST_SERVER_ENTRIES_RESPONSE_HANDLER_H

#include <ostream>
#include "ListFileEntriesResponse.h"
#include "application/PrinterService.h"
#include "infra/messaging/MessageHandler.h"

class ListServerEntriesResponseHandler : public MessageHandler {
    PrinterService& service;

    ListFileEntriesResponse deserializeMessage(std::string body);

  public:
    ListServerEntriesResponseHandler(PrinterService& service)
        : service(service){};
    void handle(Message message, MessageStreamer& messageStreamer) override;
};

#endif