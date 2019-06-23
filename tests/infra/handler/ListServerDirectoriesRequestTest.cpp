#include <gmock/gmock.h>
#include <sstream>
#include "infra/handler/ListServerDirectoriesRequest.h"

using ::testing::Eq;

TEST(ListServerDirectoriesRequestTest, SerializesResponse) {
    std::string address = "127.0.0.1";
    int port = 45120;
    ListServerDirectoriesRequest request(&address[0], port);

    std::stringstream serialized;
    serialized << request;

    EXPECT_THAT(serialized.str(), Eq("9,127.0.0.1,45120"));
}

TEST(ListServerDirectoriesRequestTest, DeserializesResponse) {
    std::stringstream serialized("9,127.0.0.1,45120");

    ListServerDirectoriesRequest response;
    serialized >> response;

    EXPECT_THAT(response.getAddress(), Eq("127.0.0.1"));
    EXPECT_THAT(response.getPort(), Eq(45120));
}
