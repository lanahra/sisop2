#include <gmock/gmock.h>
#include "infra/messaging/Message.h"

#include <sstream>

using ::testing::Eq;

TEST(MessageTest, SerializesMessage) {
    Message message("operation", "body");

    std::stringstream serialized;
    serialized << message;

    EXPECT_THAT(serialized.str(), Eq("9,operation,4,body"));
}

TEST(MessageTest, DeserializesMessage) {
    std::stringstream serialized("9,operation,4,body");

    Message message;
    serialized >> message;

    EXPECT_THAT(message.getOperation(), Eq("operation"));
    EXPECT_THAT(message.getBody(), Eq("body"));
}
