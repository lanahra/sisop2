#include "infra/messaging/BlockingMessageListener.h"
#include "infra/messaging/SocketException.h"

#include <sstream>

void BlockingMessageListener::listen() {
    try {
        tryToListen();
    } catch (SocketException e) {
        std::clog << e.what() << '\n';
        std::clog.flush();
    }
}

void BlockingMessageListener::tryToListen() {
    while (listenerLoop.isOpen()) {
        Message message = messageStreamer->receive();
        MessageHandler& handler = handlerFor(message.getOperation());
        handler.handle(message.getBody(), *messageStreamer);
    }
}

MessageHandler& BlockingMessageListener::handlerFor(
    std::string operation) {
    return *handlers.at(operation);
}
