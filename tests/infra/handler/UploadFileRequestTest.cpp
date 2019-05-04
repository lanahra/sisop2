#include <gmock/gmock.h>
#include <sstream>
#include <infra/handler/DownloadFileRequest.h>
#include "infra/handler/UploadFileRequest.h"

using ::testing::Eq;

TEST(UploadFileRequestTest, SerializesRequest) {
    File file("file_name", Timestamps(10,20,30), "body");
    UploadFileRequest request("name", file);

    std::stringstream serialized;
    serialized << request;

    EXPECT_THAT(serialized.str(), Eq("4,name,9,file_name,10,20,30,4,body"));
}

TEST(UploadFileRequestTest, DeserializesRequest) {
    std::stringstream serialized("4,name,9,file_name,10,20,30,4,body");

    UploadFileRequest request;
    serialized >> request;

    File expected("file_name", Timestamps(10,20,30), "body");
    EXPECT_THAT(request.getUsername(), Eq("name"));
    EXPECT_THAT(request.getFile(), Eq(expected));
}
