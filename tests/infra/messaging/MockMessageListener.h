#ifndef MOCK_MESSAGE_LISTENER_H
#define MOCK_MESSAGE_LISTENER_H

#include <gmock/gmock.h>
#include "infra/messaging/MessageListener.h"

class MockMessageListener : public MessageListener {
  public:
    MOCK_METHOD0(listen, void());
};

#endif
