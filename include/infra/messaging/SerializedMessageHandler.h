#ifndef SERIALIZED_MESSAGE_HANDLER_H
#define SERIALIZED_MESSAGE_HANDLER_H

#include <string>
#include "MessageHandler.h"
#include "Socket.h"

template <typename T>
class SerializedMessageHandler : public MessageHandler<std::string> {
    MessageHandler<T>& handler;

  public:
    SerializedMessageHandler(MessageHandler<T>& handler) : handler(handler){};
    void handle(std::string message, Socket& socket) override;
};

template <typename T>
void SerializedMessageHandler<T>::handle(std::string message, Socket& socket) {
    std::stringstream serialized(message);
    T deserialized;
    serialized >> deserialized;
    handler.handle(deserialized, socket);
}

#endif
