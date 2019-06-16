#ifndef SISOP2_TEMPORALSYNCHRONIZER_H
#define SISOP2_TEMPORALSYNCHRONIZER_H


#include <infra/handler/ListServerEntriesCommandHandler.h>
#include <infra/messaging/ListenerLoop.h>

class TemporalSynchronizer {
    std::shared_ptr<ListServerEntriesCommandHandler> syncCommandHandler;
    MessageStreamer& messageStreamer;
    ListenerLoop& listenerLoop;

public:
    TemporalSynchronizer(std::shared_ptr<ListServerEntriesCommandHandler> syncCommandHandler,
                         MessageStreamer &messageStreamer,
                         ListenerLoop &listenerLoop)
    : syncCommandHandler(syncCommandHandler),
      messageStreamer(messageStreamer),
      listenerLoop(listenerLoop) {};
    void start();
};


#endif