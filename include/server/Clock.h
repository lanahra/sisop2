#ifndef CLOCK_H
#define CLOCK_H

#include <ctime>

class Clock {
  public:
    virtual ~Clock() = default;
    virtual time_t now() = 0;
};

#endif
