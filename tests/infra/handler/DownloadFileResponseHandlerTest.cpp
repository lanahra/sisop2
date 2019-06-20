#include <gmock/gmock.h>
#include "../../application/MockUserService.h"
#include "../messaging/MockMessageStreamer.h"
#include "infra/handler/DownloadFileResponseHandler.h"

using ::testing::Eq;
using ::testing::StrictMock;

TEST(DownloadFileResponseHandlerTest, SavesDownloadedFile) {
    MockUserService service;
    EXPECT_CALL(service,
                saveLocal(File("second", Timestamps(1556363385, 1556363385, 1556363385), "file\nbody")));

    std::stringstream output;
    DownloadFileResponseHandler handler(service, output);
    Message response(
        "file.download.response",
        "8,username,1,6,second,1556363385,1556363385,1556363385,9,file\nbody");
    MockMessageStreamer messageStreamer;
    handler.handle(response, messageStreamer);
}

TEST(DownloadFileResponseHandlerTest, PrintsErrorMessageForFileNotFound) {
    StrictMock<MockUserService> service;

    std::stringstream output;
    DownloadFileResponseHandler handler(service, output);
    Message response(
        "file.download.response",
        "8,username,0");
    MockMessageStreamer messageStreamer;
    handler.handle(response, messageStreamer);

    EXPECT_THAT(output.str(), Eq("file not found\n"));
}