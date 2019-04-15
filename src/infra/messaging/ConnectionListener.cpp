#include "infra/messaging/ConnectionListener.h"

#include <memory>

void ConnectionListener::listen(int port) {
    socket.listen(port);
    while (listenerLoop.isOpen()) {
        std::shared_ptr<Socket> client = socket.accept();
        auto listener = factory.listenerFor(client);
        listener->listen();
    }
}
