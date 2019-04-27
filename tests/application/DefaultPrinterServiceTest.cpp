#include <gmock/gmock.h>
#include "application/DefaultPrinterService.h"

using ::testing::Eq;

TEST(DefaultPrinterServiceTest, PrintsEntries) {
    std::list<FileEntry> entries(
        {FileEntry("first", Timestamps(1556249031, 1556249031, 1556249031)),
         FileEntry("second", Timestamps(1556249031, 1556249031, 1556249031))});

    std::stringstream output;
    DefaultPrinterService service(output);
    
    service.printEntries(entries);

    EXPECT_THAT(
        output.str(),
        Eq("last modified           last accessed           last changed       "
           "     file\n2019-04-26 03:23:51     2019-04-26 03:23:51     "
           "2019-04-26 03:23:51     first\n2019-04-26 03:23:51     2019-04-26 "
           "03:23:51     2019-04-26 03:23:51     second\n"));
}