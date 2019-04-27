#include "infra/handler/ListServerEntriesCommandHandler.h"
#include <tuple>

void ListServerEntriesCommandHandler::handle(std::vector<std::string> args,
                                             MessageStreamer& messageStreamer) {
    std::ignore = args;
    Message command(operation, username, response);
    messageStreamer.send(command);
}
