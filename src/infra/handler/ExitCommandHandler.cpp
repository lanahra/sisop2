#include "infra/handler/ExitCommandHandler.h"
#include <tuple>

void ExitCommandHandler::handle(std::vector<std::string> args,
                                MessageStreamer& messageStreamer) {
    std::ignore = args;
    messageStreamer.close();
    throw ExitException();
}
