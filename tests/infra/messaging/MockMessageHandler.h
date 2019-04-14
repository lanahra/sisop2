#ifndef MOCK_MESSAGE_HANDLER_H
#define MOCK_MESSAGE_HANDLER_H

#include <gmock/gmock.h>
#include <string>
#include "infra/messaging/MessageHandler.h"
#include "infra/messaging/Socket.h"

class MockMessageHandler : public MessageHandler {
  public:
    MOCK_METHOD2(handle, void(std::string, Socket&));
};

#endif
