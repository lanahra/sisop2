#include <gmock/gmock.h>
#include "server/RemovedEntry.h"

using ::testing::Eq;

TEST(RemovedEntryTest, SerializesRemovedEntry) {
    RemovedEntry entry("file", 10);

    std::stringstream serialized;
    serialized << entry;

    EXPECT_THAT(serialized.str(), Eq("4,file,10"));
}