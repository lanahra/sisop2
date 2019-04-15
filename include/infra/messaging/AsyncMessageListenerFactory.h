#ifndef ASYNC_MESSAGE_LISTENER_FACTORY_H
#define ASYNC_MESSAGE_LISTENER_FACTORY_H

#include <map>
#include <memory>
#include "MessageListenerFactory.h"
#include "Socket.h"
#include "ListenerLoop.h"
#include "MessageHandler.h"

class AsyncMessageListenerFactory : public MessageListenerFactory {
    ListenerLoop& listenerLoop;
    std::map<std::string, std::shared_ptr<MessageHandler>> handlers;

  public:
    AsyncMessageListenerFactory(
        ListenerLoop& listenerLoop,
        std::map<std::string, std::shared_ptr<MessageHandler>> handlers)
        : listenerLoop(listenerLoop), handlers(handlers){};
    std::unique_ptr<MessageListener> listenerFor(
        std::shared_ptr<Socket> socket) override;
};

#endif
