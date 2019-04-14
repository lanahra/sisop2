#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include <string>
#include "Socket.h"

class MessageHandler {
  public:
    virtual ~MessageHandler() = default;
    virtual void handle(std::string message, Socket& socket) = 0;
};

#endif
