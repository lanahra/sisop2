#ifndef MOCK_MESSAGE_HANDLER_H
#define MOCK_MESSAGE_HANDLER_H

#include <gmock/gmock.h>
#include "infra/messaging/MessageHandler.h"
#include "infra/messaging/Socket.h"

template <typename T>
class MockMessageHandler : public MessageHandler<T> {
  public:
    MOCK_METHOD2_T(handle, void(T, Socket&));
};

#endif
