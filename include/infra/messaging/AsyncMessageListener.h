#ifndef ASYNC_MESSAGE_LISTENER_H
#define ASYNC_MESSAGE_LISTENER_H

#include "MessageListener.h"

class AsyncMessageListener : public MessageListener {
    MessageListener& listener;

  public:
    AsyncMessageListener(MessageListener& listener) : listener(listener){};
    void listen() override;
};

#endif
