#include "infra/handler/ListFileEntriesHandler.h"
#include "infra/handler/ListFileEntriesResponse.h"

#include <sstream>

void ListFileEntriesHandler::handle(Message message,
                                    MessageStreamer& messageStreamer) {
    std::string username = message.getBody();
    std::list<FileEntry> entries = service.listFileEntries(username);
    ListFileEntriesResponse fileEntries(username, entries);
    std::stringstream serialized;
    serialized << fileEntries;
    Message response(message.getResponse(), serialized.str());
    messageStreamer.send(response);
}
