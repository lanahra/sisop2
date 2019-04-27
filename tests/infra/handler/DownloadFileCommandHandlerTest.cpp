#include <gmock/gmock.h>
#include "../messaging/MockMessageStreamer.h"
#include "infra/handler/DownloadFileCommandHandler.h"

using ::testing::StrictMock;
using ::testing::Eq;

TEST(DownloadFileCommandHandlerTest, SendsDownloadFileCommand) {
    MockMessageStreamer messageStreamer;
    Message command("operation", "4,name,4,file", "response");
    EXPECT_CALL(messageStreamer, send(command));

    std::stringstream output;
    DownloadFileCommandHandler handler("name", "operation", "response", output);

    std::vector<std::string> args({"download", "file"});
    handler.handle(args, messageStreamer);
}

TEST(DownloadFileCommandHandlerTest, PrintsErrorMessageForInvalidArgs) {
    StrictMock<MockMessageStreamer> messageStreamer;

    std::stringstream output;
    DownloadFileCommandHandler handler("name", "operation", "response", output);
    handler.handle(std::vector<std::string>(), messageStreamer);

    EXPECT_THAT(output.str(), Eq("download command takes 1 argument\n"));
}