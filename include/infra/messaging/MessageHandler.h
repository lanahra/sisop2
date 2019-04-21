#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include "Message.h"
#include "MessageStreamer.h"

class MessageHandler {
  public:
    virtual ~MessageHandler() = default;
    virtual void handle(Message message, MessageStreamer& socket) = 0;
};

#endif
