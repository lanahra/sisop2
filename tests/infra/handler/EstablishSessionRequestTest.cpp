#include <gmock/gmock.h>
#include "infra/handler/EstablishSessionRequest.h"

#include <sstream>

using ::testing::Eq;

TEST(EstablishSessionRequestTest, SerializesRequest) {
    EstablishSessionRequest request("name");

    std::stringstream serialized;
    serialized << request;

    EXPECT_THAT(serialized.str(), "4,name");
}

TEST(EstablishSessionRequestTest, DeserializesRequest) {
    std::stringstream serialized("4,name");

    EstablishSessionRequest request;
    serialized >> request;

    EXPECT_THAT(request.getUsername(), Eq("name"));
}
