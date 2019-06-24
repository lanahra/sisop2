#include "infra/handler/StartAreYouAliveCommandHandler.h"

void StartAreYouAliveCommandHandler::handle(std::vector<std::string> args,
                                            MessageStreamer &messageStreamer) {
    std::ignore = args;
    Message command(operation, "");
    messageStreamer.send(command);
}
