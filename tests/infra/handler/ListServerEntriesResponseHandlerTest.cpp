#include <gmock/gmock.h>
#include "../../application/MockPrinterService.h"
#include "../messaging/MockMessageStreamer.h"
#include "infra/handler/ListServerEntriesResponseHandler.h"

using ::testing::Eq;

TEST(ListServerEntriesResponseHandlerTest, FormatsFileEntriesToOutput) {
    MockPrinterService service;
    std::list<FileEntry> entries(
        {FileEntry("first", Timestamps(1556249031, 1556249031, 1556249031)),
         FileEntry("second", Timestamps(1556249031, 1556249031, 1556249031))});
    EXPECT_CALL(service, printEntries(entries));

    ListServerEntriesResponseHandler handler(service);
    Message response("file.list.response",
                     "2,5,first,1556249031,1556249031,1556249031,6,second,"
                     "1556249031,1556249031,1556249031");
    MockMessageStreamer messageStreamer;
    handler.handle(response, messageStreamer);
}