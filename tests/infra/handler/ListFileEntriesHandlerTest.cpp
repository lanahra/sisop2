#include <gmock/gmock.h>
#include "infra/handler/ListFileEntriesHandler.h"
#include "../messaging/MockMessageStreamer.h"
#include "../../application/MockUserService.h"

using ::testing::Return;

TEST(ListFileEntriesHandlerTest, ListUserFileEntries) {
    MockUserService service;
    Timestamps timestamps(10, 20, 30);
    EXPECT_CALL(service, listFileEntries("name"))
        .WillOnce(Return(std::list<FileEntry>{
            FileEntry("first", timestamps), FileEntry("second", timestamps)}));


    MockMessageStreamer messageStreamer;
    Message response("file.list.response",
                    "4,name,2,5,first,10,20,30,6,second,10,20,30");
    EXPECT_CALL(messageStreamer, send(response));

    ListFileEntriesHandler handler(service);
    Message message("file.list.request", "name", "file.list.response");
    handler.handle(message, messageStreamer);
}
