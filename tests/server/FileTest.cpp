#include <gmock/gmock.h>
#include "server/File.h"

using ::testing::Eq;

TEST(FileTest, SerializesFile) {
    Timestamps timestamps(10, 20, 30);
    File file("name", timestamps, "file body with spaces and line\n breaks");

    std::stringstream serialized;
    serialized << file;

    EXPECT_THAT(
        serialized.str(),
        Eq("4,name,10,20,30,38,file body with spaces and line\n breaks"));
}

TEST(FileTest, DeserializesFile) {
    std::stringstream serialized(
        "4,name,10,20,30,38,file body with spaces and line\n breaks");

    File file;
    serialized >> file;

    Timestamps timestamps(10, 20, 30);
    File expected("name", timestamps, "file body with spaces and line\n breaks");
    EXPECT_THAT(file, Eq(expected));
}
