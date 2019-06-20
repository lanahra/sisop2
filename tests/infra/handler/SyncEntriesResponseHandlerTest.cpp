#include <gmock/gmock.h>
#include "../../application/MockUserService.h"
#include "../messaging/MockMessageStreamer.h"
#include "infra/handler/SyncEntriesResponseHandler.h"

using ::testing::Return;

TEST(SyncEntriesResponseHandlerTest, SendsSyncOperations) {
    MockUserService service;
    EXPECT_CALL(
        service,
        syncUser(
            "name",
            std::list<FileEntry>(
                {FileEntry("first",
                           Timestamps(1556249031, 1556249031, 1556249031)),
                 FileEntry("second",
                           Timestamps(1556249031, 1556249031, 1556249031))})))
        .WillOnce(Return(std::list<SyncOperation>(
            {SyncOperation(SyncOperation::DOWNLOAD, "one"),
             SyncOperation(SyncOperation::DELETE, "two"),
             SyncOperation(SyncOperation::UPLOAD, "three")})));

    File three("three", Timestamps(1556249031, 1556249031, 1556249031), "body");
    EXPECT_CALL(service, getFile("name", "three")).WillOnce(Return(three));

    SyncEndpoints endpoints
        = SyncEndpoints::Builder()
              .withDownloadFile("download.operation", "download.response")
              .withRemoveFile("remove.operation")
              .withUploadFile("upload.operation")
              .build();

    SyncEntriesResponseHandler handler(endpoints, service);

    Message response("file.list.response",
                     "4,name,2,5,first,1556249031,1556249031,1556249031,6,second,"
                     "1556249031,1556249031,1556249031");

    MockMessageStreamer messageStreamer;
    EXPECT_CALL(
        messageStreamer,
        send(Message(
            "download.operation", "4,name,3,one", "download.response")));
    EXPECT_CALL(messageStreamer,
                send(Message("remove.operation", "4,name,3,two")));
    EXPECT_CALL(messageStreamer,
                send(Message(
                    "upload.operation",
                    "4,name,5,three,1556249031,1556249031,1556249031,4,body")));

    handler.handle(response, messageStreamer);
}