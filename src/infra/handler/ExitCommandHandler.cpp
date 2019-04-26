#include "infra/handler/ExitCommandHandler.h"

void ExitCommandHandler::handle(std::vector<std::string> args,
                                MessageStreamer& messageStreamer) {
    messageStreamer.close();
    throw ExitException();
}
