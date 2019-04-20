#include "infra/handler/ListFileEntriesHandler.h"
#include "infra/handler/ListFileEntriesResponse.h"

#include <sstream>

void ListFileEntriesHandler::handle(std::string name,
                                    MessageStreamer& messageStreamer) {
    std::list<FileEntry> entries = service.listFileEntries(name);
    ListFileEntriesResponse response(entries);
    std::stringstream serialized;
    serialized << response;
    Message message("file.list.response", serialized.str());
    messageStreamer.send(message);
}
