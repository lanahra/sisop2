#ifndef CONNECTION_LISTENER_H
#define CONNECTION_LISTENER_H

#include "Socket.h"
#include "ListenerLoop.h"
#include "MessageListenerFactory.h"

class ConnectionListener {
    Socket& socket;
    ListenerLoop& listenerLoop;
    MessageListenerFactory& factory;

  public:
    ConnectionListener(Socket& socket,
                       ListenerLoop& listenerLoop,
                       MessageListenerFactory& factory)
        : socket(socket), listenerLoop(listenerLoop), factory(factory){};
    void listen(int port);
};

#endif
