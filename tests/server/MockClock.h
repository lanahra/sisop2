#ifndef MOCK_CLOCK_H
#define MOCK_CLOCK_H

#include <gmock/gmock.h>
#include "server/Clock.h"

class MockClock : public Clock {
  public:
    MOCK_METHOD0(now, time_t());
};

#endif