#include "infra/messaging/ConnectionListener.h"

void ConnectionListener::listen(int port) {
    socket.listen(port);
    while (listenerLoop.isOpen()) {
        socket.accept();
    }
}
