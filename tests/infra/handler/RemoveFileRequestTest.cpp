#include <gmock/gmock.h>
#include <sstream>
#include "infra/handler/RemoveFileRequest.h"

using ::testing::Eq;

TEST(RemoveFileRequestTest, SerializesRequest) {
    RemoveFileRequest request("name", "file");

    std::stringstream serialized;
    serialized << request;

    EXPECT_THAT(serialized.str(), Eq("4,name,4,file"));
}

TEST(RemoveFileRequestTest, DeserializesRequest) {
    std::stringstream serialized("4,name,4,file");

    RemoveFileRequest request;
    serialized >> request;

    RemoveFileRequest expected("name", "file");
    EXPECT_THAT(request, Eq(expected));
}