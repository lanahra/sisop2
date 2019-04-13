#include <gmock/gmock.h>
#include "infra/messaging/ListenerLoop.h"

class MockListenerLoop : public ListenerLoop {
  public:
    MOCK_METHOD0(isOpen, bool());
};
