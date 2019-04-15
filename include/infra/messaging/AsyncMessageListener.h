#ifndef ASYNC_MESSAGE_LISTENER_H
#define ASYNC_MESSAGE_LISTENER_H

#include <memory>
#include "MessageListener.h"

class AsyncMessageListener : public MessageListener {
    std::unique_ptr<MessageListener> listener;

  public:
    AsyncMessageListener(std::unique_ptr<MessageListener> listener)
        : listener(std::move(listener)){};
    void listen() override;
};

#endif
