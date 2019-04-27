#include <gmock/gmock.h>
#include "../../application/MockPrinterService.h"
#include "../../application/MockUserService.h"
#include "../messaging/MockMessageStreamer.h"
#include "infra/handler/ListClientEntriesCommandHandler.h"

using ::testing::Return;

TEST(ListClientEntriesCommandHandlerTest, PrintsClientEntries) {
    MockUserService userService;
    std::list<FileEntry> entries(
        {FileEntry("first", Timestamps(1556249031, 1556249031, 1556249031)),
         FileEntry("second", Timestamps(1556249031, 1556249031, 1556249031))});
    EXPECT_CALL(userService, listFileEntries("user")).WillOnce(Return(entries));

    MockPrinterService printerService;
    EXPECT_CALL(printerService, printEntries(entries));

    ListClientEntriesCommandHandler handler("user", userService, printerService);

    MockMessageStreamer messageStreamer;
    handler.handle(std::vector<std::string>(), messageStreamer);
}