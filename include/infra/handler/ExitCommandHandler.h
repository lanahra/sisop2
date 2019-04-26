#ifndef EXIT_COMMAND_HANDLER_H
#define EXIT_COMMAND_HANDLER_H

#include <stdexcept>
#include "infra/messaging/CommandHandler.h"

class ExitCommandHandler : public CommandHandler {
  public:
    void handle(std::vector<std::string> args,
                MessageStreamer& messageStreamer) override;
};

class ExitException : public std::runtime_error {
  public:
    ExitException() : std::runtime_error(""){};
};

#endif