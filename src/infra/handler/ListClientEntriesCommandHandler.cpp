#include "infra/handler/ListClientEntriesCommandHandler.h"
#include <tuple>

void ListClientEntriesCommandHandler::handle(std::vector<std::string> args,
                                             MessageStreamer& messageStreamer) {
    std::ignore = args;
    std::ignore = messageStreamer;
    std::list<FileEntry> entries = userService.listFileEntries(username);
    printerService.printEntries(entries);
}
