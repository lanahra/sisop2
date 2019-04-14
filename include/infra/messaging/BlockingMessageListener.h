#ifndef BLOCKING_MESSAGE_LISTENER_H
#define BLOCKING_MESSAGE_LISTENER_H

#include "MessageListener.h"
#include "Socket.h"
#include "ListenerLoop.h"

class BlockingMessageListener : public MessageListener {
    Socket& socket;
    ListenerLoop& listenerLoop;

  public:
    BlockingMessageListener(Socket& socket, ListenerLoop& listenerLoop)
        : socket(socket), listenerLoop(listenerLoop){};
    void listen() override;
};

#endif
