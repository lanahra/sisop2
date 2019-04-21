#include "infra/handler/ListFileEntriesHandler.h"
#include "infra/handler/ListFileEntriesResponse.h"

#include <sstream>

void ListFileEntriesHandler::handle(Message message,
                                    MessageStreamer& messageStreamer) {
    std::list<FileEntry> entries = service.listFileEntries(message.getBody());
    ListFileEntriesResponse fileEntries(entries);
    std::stringstream serialized;
    serialized << fileEntries;
    Message response(message.getResponse(), serialized.str());
    messageStreamer.send(response);
}
