#include "infra/messaging/BlockingMessageListener.h"

void BlockingMessageListener::listen() {
    while (listenerLoop.isOpen()) {
        int length = socket.readInt();
        std::string body = socket.read(length);
    }
}
