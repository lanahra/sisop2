#include <gmock/gmock.h>
#include <sstream>
#include "infra/handler/ListServerDirectoriesResponse.h"

using ::testing::Eq;

TEST(ListServerDirectoriesResponseTest, SerializesResponse) {
    std::vector<std::string> usernames{"name1", "name2", "name3"};
    ListServerDirectoriesResponse response(usernames);

    std::stringstream serialized;
    serialized << response;

    EXPECT_THAT(serialized.str(), Eq("3,5,name1,5,name2,5,name3"));
}

TEST(ListServerDirectoriesResponseTest, DeserializesResponse) {
    std::stringstream serialized("3,5,name1,5,name2,5,name3");

    ListServerDirectoriesResponse response;
    serialized >> response;

    std::vector<std::string> expected{"name1", "name2", "name3"};
    EXPECT_THAT(response.getUsernames(), Eq(expected));
}
