#ifndef BLOCKING_MESSAGE_LISTENER_H
#define BLOCKING_MESSAGE_LISTENER_H

#include <map>
#include <memory>
#include <string>
#include "MessageListener.h"
#include "Socket.h"
#include "ListenerLoop.h"
#include "MessageHandler.h"
#include "Message.h"

class BlockingMessageListener : public MessageListener {
    Socket& socket;
    ListenerLoop& listenerLoop;
    std::map<std::string, std::shared_ptr<MessageHandler>> handlers;

    Message messageFrom(std::string serialized);
    std::shared_ptr<MessageHandler> handlerFor(std::string operation);

  public:
    BlockingMessageListener(
        Socket& socket,
        ListenerLoop& listenerLoop,
        std::map<std::string, std::shared_ptr<MessageHandler>> handlers)
        : socket(socket), listenerLoop(listenerLoop), handlers(handlers){};
    void listen() override;
};

#endif
