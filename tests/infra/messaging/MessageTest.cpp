#include <gmock/gmock.h>
#include "infra/messaging/Message.h"

#include <sstream>

using ::testing::Eq;

TEST(MessageTest, SerializesMessage) {
    Message message("operation", "body");

    std::stringstream serialized;
    serialized << message;

    EXPECT_THAT(serialized.str(), Eq("9,operation,4,body,0,"));
}

TEST(MessageTest, DeserializesMessage) {
    std::stringstream serialized("9,operation,4,body,0,");

    Message message;
    serialized >> message;

    Message expected("operation", "body");
    EXPECT_THAT(message, Eq(expected));
}

TEST(MessageTest, SerializesMessageWithResponse) {
    Message message("operation", "body", "response");

    std::stringstream serialized;
    serialized << message;

    EXPECT_THAT(serialized.str(), Eq("9,operation,4,body,8,response"));
}

TEST(MessageTest, DeserializesMessageWithResponse) {
    std::stringstream serialized("9,operation,4,body,8,response");

    Message message;
    serialized >> message;

    Message expected("operation", "body", "response");
    EXPECT_THAT(message, Eq(expected));
}
