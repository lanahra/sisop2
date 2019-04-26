#include <gmock/gmock.h>
#include "../messaging/MockMessageStreamer.h"
#include "infra/handler/ExitCommandHandler.h"

TEST(ExitCommandHandlerTest, ClosesMessageStreamerAndThrowsExitException) {
    MockMessageStreamer messageStreamer;
    EXPECT_CALL(messageStreamer, close());

    ExitCommandHandler handler;
    EXPECT_THROW(handler.handle(std::vector<std::string>(), messageStreamer),
                 ExitException);
}