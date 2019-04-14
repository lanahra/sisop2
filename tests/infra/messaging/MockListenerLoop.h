#ifndef MOCK_LISTENER_LOOP_H
#define MOCK_LISTENER_LOOP_H

#include <gmock/gmock.h>
#include "infra/messaging/ListenerLoop.h"

class MockListenerLoop : public ListenerLoop {
  public:
    MOCK_METHOD0(isOpen, bool());
};

#endif
