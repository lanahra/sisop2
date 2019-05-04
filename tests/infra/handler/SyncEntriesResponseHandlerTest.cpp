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
             /* TODO SyncOperation(SyncOperation::UPLOAD, "three") */})));
    /* TODO
    File three("three", Timestamps(1556249031, 1556249031, 1556249031), "body");
    EXPECT_CALL(service, getFile("name", "three")).WillOnce(Return(three));
     */

    SyncEndpoints endpoints
        = SyncEndpoints::Builder()
              .withListEntries("list.operation", "list.response")
              .withDownloadFile("download.operation", "download.response")
              .withRemoveFile("remove.operation")
              .withUploadFile("upload.operation")
              .build();

    SyncEntriesResponseHandler handler("name", endpoints, service);

    Message response("file.list.response",
                     "2,5,first,1556249031,1556249031,1556249031,6,second,"
                     "1556249031,1556249031,1556249031");

    MockMessageStreamer messageStreamer;
    EXPECT_CALL(
        messageStreamer,
        send(Message(
            "download.operation", "4,name,3,one", "download.response")));
    EXPECT_CALL(messageStreamer,
                send(Message("remove.operation", "4,name,3,two")));
    /* TODO
    EXPECT_CALL(messageStreamer,
                send(Message("upload.operation", "4,name,5,three")));
     */
    EXPECT_CALL(messageStreamer,
                send(Message("list.operation", "name", "list.response")));

    handler.handle(response, messageStreamer);
}