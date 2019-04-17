#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include <string>
#include "MessageStreamer.h"

class MessageHandler {
  public:
    virtual ~MessageHandler() = default;
    virtual void handle(std::string message, MessageStreamer& socket) = 0;
};

#endif
