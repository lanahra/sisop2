#include <gmock/gmock.h>
#include <chrono>
#include <thread>
#include "server/SystemClock.h"

using ::testing::Lt;

TEST(SystemClockTest, ReturnsCurrentTime) {
    auto time = std::chrono::system_clock::now();
    time_t before = std::chrono::system_clock::to_time_t(time);
    std::this_thread::sleep_for(std::chrono::seconds(1));

    SystemClock clock;
    time_t now = clock.now();
    std::this_thread::sleep_for(std::chrono::seconds(1));

    time = std::chrono::system_clock::now();
    time_t after = std::chrono::system_clock::to_time_t(time);

    EXPECT_THAT(before, Lt(now));
    EXPECT_THAT(now, Lt(after));
}