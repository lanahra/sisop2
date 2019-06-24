#ifndef SISOP2_TEMPORALSYNCHRONIZER_H
#define SISOP2_TEMPORALSYNCHRONIZER_H


#include <infra/handler/ListServerEntriesCommandHandler.h>
#include <infra/messaging/ListenerLoop.h>

class TemporalSynchronizer {
    std::shared_ptr<CommandHandler> commandHandler;
    MessageStreamer& messageStreamer;
    ListenerLoop& listenerLoop;
    int sleepInMillis;

public:
    TemporalSynchronizer(std::shared_ptr<CommandHandler> commandHandler,
                         MessageStreamer &messageStreamer,
                         ListenerLoop &listenerLoop, int sleepInMillis)
    : commandHandler(commandHandler),
      messageStreamer(messageStreamer),
      listenerLoop(listenerLoop),
      sleepInMillis(sleepInMillis) {};
    void start();
};


#endif