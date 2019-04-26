#ifndef BLOCKING_COMMAND_LISTENER_H
#define BLOCKING_COMMAND_LISTENER_H

#include <istream>
#include <map>
#include <memory>
#include "CommandHandler.h"
#include "ListenerLoop.h"
#include "MessageListener.h"
#include "MessageStreamer.h"

class BlockingCommandListener : public MessageListener {
    std::istream& input;
    ListenerLoop& listenerLoop;
    std::shared_ptr<MessageStreamer> messageStreamer;
    std::map<std::string, std::shared_ptr<CommandHandler>> handlers;

    void tryToListen();
    std::vector<std::string> argsFrom(std::string line);
    CommandHandler& handlerFor(std::vector<std::string> args);

  public:
    BlockingCommandListener(
        std::istream& input,
        ListenerLoop& listenerLoop,
        std::shared_ptr<MessageStreamer> messageStreamer,
        std::map<std::string, std::shared_ptr<CommandHandler>> handlers)
        : input(input),
          listenerLoop(listenerLoop),
          messageStreamer(messageStreamer),
          handlers(handlers){};
    void listen() override;
    bool handlerExistsFor(std::vector<std::string> args);
};

#endif