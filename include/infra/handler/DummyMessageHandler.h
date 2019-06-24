#ifndef SISOP2_DUMMYMESSAGEHANDLER_H
#define SISOP2_DUMMYMESSAGEHANDLER_H


#include <infra/messaging/MessageHandler.h>

class DummyMessageHandler : public MessageHandler{

  public:
    DummyMessageHandler(){};
    void handle(Message message, MessageStreamer& messageStreamer) override;
};


#endif
