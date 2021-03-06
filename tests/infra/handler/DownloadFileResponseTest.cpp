#include <gmock/gmock.h>
#include <sstream>
#include "infra/handler/DownloadFileResponse.h"

using ::testing::Eq;

TEST(DownloadFileResponseTest, SerializesResponseForNotFound) {
    DownloadFileResponse response("username");

    std::stringstream serialized;
    serialized << response;

    EXPECT_THAT(serialized.str(), Eq("8,username,0"));
}


TEST(DownloadFileResponseTest, SerializesResponseForFileFound) {
    File file("name", Timestamps(10,20,30), "body");
    DownloadFileResponse response("username", file);

    std::stringstream serialized;
    serialized << response;

    EXPECT_THAT(serialized.str(), Eq("8,username,1,4,name,10,20,30,4,body"));
}

TEST(DownloadFileResponseTest, DeserializesResponseForNotFound) {
    std::stringstream serialized("8,username,0");

    DownloadFileResponse response;
    serialized >> response;

    EXPECT_THAT(response.hasFile(), Eq(false));
}

TEST(DownloadFileResponseTest, DeserializesResponseForFileFound) {
    std::stringstream serialized("8,username,1,4,name,10,20,30,4,body");
    
    DownloadFileResponse response;
    serialized >> response;

    File expected("name", Timestamps(10,20,30), "body");
    EXPECT_THAT(response.hasFile(), Eq(true));
    EXPECT_THAT(response.getFile(), Eq(expected));
}
