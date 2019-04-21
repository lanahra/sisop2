#include <gmock/gmock.h>
#include <sstream>
#include "infra/handler/DownloadFileRequest.h"

using ::testing::Eq;

TEST(DownloadFileRequestTest, SerializesRequest) {
    DownloadFileRequest request("name", "file");

    std::stringstream serialized;
    serialized << request;
    
    EXPECT_THAT(serialized.str(), Eq("4,name,4,file"));
}

TEST(DownloadFileRequestTest, DeserializesRequest) {
    std::stringstream serialized("4,name,4,file");

    DownloadFileRequest request;
    serialized >> request;

    DownloadFileRequest expected("name", "file");
    EXPECT_THAT(request, Eq(expected));
}
