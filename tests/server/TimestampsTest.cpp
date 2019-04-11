#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include "server/Timestamps.h"

using ::testing::Eq;

TEST(TimestampsTest, SerializesTimestamps) {
    Timestamps timestamps(10, 20, 30);

    std::stringstream serialized;
    serialized << timestamps;

    EXPECT_THAT(serialized.str(), Eq("10,20,30"));
}

TEST(TimestampsTest, DeserializesTimestamps) {
    std::stringstream serialized("10,20,30");

    Timestamps timestamps;
    serialized >> timestamps;

    Timestamps expected(10, 20, 30);
    EXPECT_THAT(timestamps, Eq(expected));
}
