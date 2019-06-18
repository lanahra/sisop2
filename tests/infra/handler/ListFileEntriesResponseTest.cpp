#include <gmock/gmock.h>
#include <sstream>
#include "infra/handler/ListFileEntriesResponse.h"

using ::testing::Eq;

TEST(ListFileEntriesResponseTest, SerializesResponse) {
    Timestamps timestamps(10, 20, 30);
    std::list<FileEntry> entries{FileEntry("first", timestamps),
                                 FileEntry("second", timestamps)};
    std::string username = "name";
    ListFileEntriesResponse response(&username[0], entries);

    std::stringstream serialized;
    serialized << response;

    EXPECT_THAT(serialized.str(), Eq("4,name,2,5,first,10,20,30,6,second,10,20,30"));
}

TEST(ListFileEntriesResponseTest, DeserializesResponse) {
    std::stringstream serialized("4,name,2,5,first,10,20,30,6,second,10,20,30");

    ListFileEntriesResponse response;
    serialized >> response;

    Timestamps timestamps(10, 20, 30);
    std::list<FileEntry> expected{FileEntry("first", timestamps),
                                  FileEntry("second", timestamps)};
    EXPECT_THAT(response.getUsername(), Eq("name"));
    EXPECT_THAT(response.getEntries(), Eq(expected));
}
