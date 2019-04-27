#include "infra/handler/ListServerEntriesCommandHandler.h"

void ListServerEntriesCommandHandler::handle(std::vector<std::string> args,
                                             MessageStreamer& messageStreamer) {
    Message command(operation, username, response);
    messageStreamer.send(command);
}
