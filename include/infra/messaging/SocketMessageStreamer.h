#ifndef SOCKET_MESSAGE_STREAMER_H
#define SOCKET_MESSAGE_STREAMER_H

#include <memory>
#include <mutex>
#include "MessageStreamer.h"
#include "Message.h"
#include "Socket.h"

class SocketMessageStreamer : public MessageStreamer {
    std::shared_ptr<Socket> socket;
    std::mutex mutex;

    Message messageFrom(std::string serialized);
    std::string serializedFrom(Message message);

  public:
    SocketMessageStreamer(std::shared_ptr<Socket> socket) : socket(socket){};
    Message receive();
    void send(Message message);
    void close() override;
    std::shared_ptr<Socket> getSocket() override;
};

#endif
