#ifndef BLOCKING_MESSAGE_LISTENER_H
#define BLOCKING_MESSAGE_LISTENER_H

#include <map>
#include <memory>
#include <string>
#include "MessageListener.h"
#include "MessageStreamer.h"
#include "ListenerLoop.h"
#include "MessageHandler.h"
#include "Message.h"

class BlockingMessageListener : public MessageListener {
    std::shared_ptr<MessageStreamer> messageStreamer;
    ListenerLoop& listenerLoop;
    std::map<std::string, std::shared_ptr<MessageHandler>> handlers;

    void tryToListen();
    MessageHandler& handlerFor(std::string operation);

  public:
    BlockingMessageListener(
        std::shared_ptr<MessageStreamer> messageStreamer,
        ListenerLoop& listenerLoop,
        std::map<std::string, std::shared_ptr<MessageHandler>> handlers)
        : messageStreamer(messageStreamer),
          listenerLoop(listenerLoop),
          handlers(handlers){};
    void listen() override;
};

#endif
