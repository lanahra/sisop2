#ifndef LIST_SERVER_ENTRIES_RESPONSE_HANDLER_H
#define LIST_SERVER_ENTRIES_RESPONSE_HANDLER_H

#include <ostream>
#include "ListFileEntriesResponse.h"
#include "infra/messaging/MessageHandler.h"

class ListServerEntriesResponseHandler : public MessageHandler {
    std::ostream& output;

    ListFileEntriesResponse deserializeMessage(std::string body);
    void printHeader();
    void printEntries(std::list<FileEntry> list);
    std::string formatTimestamp(time_t time);

  public:
    ListServerEntriesResponseHandler(std::ostream& output) : output(output){};
    void handle(Message message, MessageStreamer& messageStreamer) override;
};

#endif