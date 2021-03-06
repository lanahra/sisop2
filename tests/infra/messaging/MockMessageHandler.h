#ifndef MOCK_MESSAGE_HANDLER_H
#define MOCK_MESSAGE_HANDLER_H

#include <gmock/gmock.h>
#include "infra/messaging/Message.h"
#include "infra/messaging/MessageHandler.h"
#include "infra/messaging/MessageStreamer.h"

class MockMessageHandler : public MessageHandler {
  public:
    MOCK_METHOD2(handle, void(Message, MessageStreamer&));
};

#endif
