#include "server/SystemClock.h"
#include <chrono>

time_t SystemClock::now() {
    auto time = std::chrono::system_clock::now();
    return std::chrono::system_clock::to_time_t(time);
}
