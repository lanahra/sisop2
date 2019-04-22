#ifndef SYSTEM_CLOCK_H
#define SYSTEM_CLOCK_H

#include "Clock.h"

class SystemClock : public Clock {
  public:
    time_t now() override;
};

#endif
