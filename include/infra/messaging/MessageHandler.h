#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include "Socket.h"

template <typename T>
class MessageHandler {
  public:
    virtual ~MessageHandler() = default;
    virtual void handle(T message, Socket& socket) = 0;
};

#endif
