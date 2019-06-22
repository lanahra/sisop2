#include <gmock/gmock.h>
#include "../../application/MockUserService.h"
#include "../messaging/MockMessageStreamer.h"
#include "infra/handler/RemoveFileHandler.h"
#include "../../server/MockReplicaManagers.h"

TEST(RemoveFileHandlerTest, RemovesUserFile) {
    MockUserService service;
    MockReplicaManagers mockReplicaManagers;
    EXPECT_CALL(service, removeFile("name", "file"));

    MockMessageStreamer messageStreamer;

    RemoveFileHandler handler(service, mockReplicaManagers);
    Message request("file.remove.request", "4,name,4,file");
    handler.handle(request, messageStreamer);
}