#include <gmock/gmock.h>
#include <sstream>
#include "server/FileEntry.h"


using ::testing::Eq;

TEST(FileEntryTest, SerializesFileEntry) {
    Timestamps timestamps(10, 20, 30);
    FileEntry entry("file", timestamps);

    std::stringstream serialized;
    serialized << entry;

    EXPECT_THAT(serialized.str(), Eq("4,file,10,20,30"));
}

TEST(FileEntryTest, DeserializesFileEntry) {
    std::stringstream serialized("4,file,10,20,30");

    FileEntry entry;
    serialized >> entry;

    Timestamps timestamps(10, 20, 30);
    FileEntry expected("file", timestamps);
    EXPECT_THAT(entry, Eq(expected));
}
