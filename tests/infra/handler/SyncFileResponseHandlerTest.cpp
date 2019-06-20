#include <gmock/gmock.h>
#include "../../application/MockUserService.h"
#include "../messaging/MockMessageStreamer.h"
#include "infra/handler/SyncFileResponseHandler.h"

using ::testing::Eq;
using ::testing::StrictMock;

TEST(SyncFileResponseHandlerTest, SavesDownloadedFile) {
    MockUserService service;
    EXPECT_CALL(service,
                saveFile("username",
                     File("second",
                          Timestamps(1556363385, 1556363385, 1556363385),
                          "file\nbody")));

    std::stringstream output;
    SyncFileResponseHandler handler(service);
    Message response(
        "file.download.response",
        "8,username,1,6,second,1556363385,1556363385,1556363385,9,file\nbody");
    MockMessageStreamer messageStreamer;
    handler.handle(response, messageStreamer);
}

TEST(SyncFileResponseHandlerTest, DoNotSaveForFileNotFound) {
    StrictMock<MockUserService> service;

    std::stringstream output;
    SyncFileResponseHandler handler(service);
    Message response("file.download.response", "8,username,0");
    MockMessageStreamer messageStreamer;
    handler.handle(response, messageStreamer);
}