#include <gmock/gmock.h>
#include "../../application/MockUserService.h"
#include "../messaging/MockMessageStreamer.h"
#include "infra/handler/DownloadFileHandler.h"
#include "infra/repository/FileNotFoundException.h"

using ::testing::Return;
using ::testing::Throw;

TEST(DownloadFileHandlerTest, DownloadsUserFile) {
    MockUserService service;
    EXPECT_CALL(service, getFile("name", "file"))
        .WillOnce(Return(File("file", Timestamps(10, 20, 30), "body")));

    MockMessageStreamer messageStreamer;
    Message response("file.download.response", "1,4,file,10,20,30,4,body");
    EXPECT_CALL(messageStreamer, send(response));

    DownloadFileHandler handler(service);
    Message request("file.download.request", "4,name,4,file", "file.download.response");
    handler.handle(request, messageStreamer);
}

TEST(DownloadFileHandlerTest, RespondsFileNotFound) {
    MockUserService service;
    EXPECT_CALL(service, getFile("name", "file"))
        .WillOnce(Throw(FileNotFoundException("file")));

    MockMessageStreamer messageStreamer;
    Message response("file.download.response", "0");
    EXPECT_CALL(messageStreamer, send(response));

    DownloadFileHandler handler(service);
    Message request("file.download.request", "4,name,4,file", "file.download.response");
    handler.handle(request, messageStreamer);
}