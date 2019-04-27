#include <gmock/gmock.h>
#include "infra/handler/ListServerEntriesCommandHandler.h"
#include "../messaging/MockMessageStreamer.h"

TEST(ListServerEntriesCommandHandlerTest, SendsListEntriesCommand) {
    Message message("operation", "name", "response");
    MockMessageStreamer messageStreamer;
    EXPECT_CALL(messageStreamer, send(message));

    ListServerEntriesCommandHandler handler("name", "operation", "response");
    handler.handle(std::vector<std::string>(), messageStreamer);
}