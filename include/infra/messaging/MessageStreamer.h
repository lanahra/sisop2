#ifndef MESSAGE_STREAMER_H
#define MESSAGE_STREAMER_H

#include "Message.h"
#include "Socket.h"

class MessageStreamer {
  public:
    virtual ~MessageStreamer() = default;
    virtual Message receive() = 0;
    virtual void send(Message message) = 0;
    virtual void close() = 0;
    virtual std::shared_ptr<Socket> getSocket() = 0;
};

#endif
