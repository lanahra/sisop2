#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <vector>
#include "MessageStreamer.h"

class CommandHandler {
  public:
    virtual ~CommandHandler() = default;
    virtual void handle(std::vector<std::string> args,
                   MessageStreamer& messageStreamer)
        = 0;
};

#endif