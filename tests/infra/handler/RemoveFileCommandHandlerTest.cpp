#include <gmock/gmock.h>
#include "../messaging/MockMessageStreamer.h"
#include "infra/handler/RemoveFileCommandHandler.h"

using ::testing::StrictMock;
using ::testing::Eq;

TEST(RemoveFileCommandHandler, SendsRemoveFileCommand) {
    MockMessageStreamer messageStreamer;
    Message command("operation", "4,name,4,file");
    EXPECT_CALL(messageStreamer, send(command));

    std::stringstream output;
    RemoveFileCommandHandler handler("name", "operation", output);

    std::vector<std::string> args({"remove", "file"});
    handler.handle(args, messageStreamer);
}

TEST(RemoveFileCommandHandler, PrintsErrorMessageForInvalidArgs) {
    StrictMock<MockMessageStreamer> messageStreamer;

    std::stringstream output;
    RemoveFileCommandHandler handler("name", "operation", output);
    handler.handle(std::vector<std::string>(), messageStreamer);

    EXPECT_THAT(output.str(), Eq("delete command takes 1 argument\n"));
}