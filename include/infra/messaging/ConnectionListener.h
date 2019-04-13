#ifndef CONNECTION_LISTENER_H
#define CONNECTION_LISTENER_H

#include "Socket.h"
#include "ListenerLoop.h"

class ConnectionListener {
    Socket& socket;
    ListenerLoop& listenerLoop;

  public:
    ConnectionListener(Socket& socket, ListenerLoop& listenerLoop)
        : socket(socket), listenerLoop(listenerLoop){};
    void listen(int port);
};

#endif
