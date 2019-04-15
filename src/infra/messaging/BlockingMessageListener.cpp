#include "infra/messaging/BlockingMessageListener.h"

#include <sstream>

void BlockingMessageListener::listen() {
    while (listenerLoop.isOpen()) {
        int length = socket->readInt();
        std::string serialized = socket->read(length);
        Message message = messageFrom(serialized);
        std::shared_ptr<MessageHandler> handler
            = handlerFor(message.getOperation());
        handler->handle(message.getBody(), *socket);
    }
}

Message BlockingMessageListener::messageFrom(std::string serialized) {
    std::stringstream s(serialized);
    Message message;
    s >> message;
    return message;
}

std::shared_ptr<MessageHandler> BlockingMessageListener::handlerFor(
    std::string operation) {
    return handlers.at(operation);
}
