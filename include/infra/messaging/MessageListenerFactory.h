#ifndef MESSAGE_LISTENER_FACTORY_H
#define MESSAGE_LISTENER_FACTORY_H

#include <memory>
#include "Socket.h"
#include "MessageListener.h"

class MessageListenerFactory {
  public:
    virtual ~MessageListenerFactory() = default;
    virtual std::unique_ptr<MessageListener> listenerFor(
        std::shared_ptr<Socket> socket)
        = 0;
};

#endif
