#include <gmock/gmock.h>
#include "../messaging/MockMessageStreamer.h"
#include "infra/handler/ListServerEntriesResponseHandler.h"

using ::testing::Eq;

TEST(ListServerEntriesResponseHandlerTest, FormatsFileEntriesToOutput) {
    MockMessageStreamer messageStreamer;

    Message response("file.list.response",
                     "2,5,first,1556249031,1556249031,1556249031,6,second,"
                     "1556249031,1556249031,1556249031");

    std::stringstream output;
    ListServerEntriesResponseHandler handler(output);
    handler.handle(response, messageStreamer);

    EXPECT_THAT(
        output.str(),
        Eq("last modified           last accessed           last changed       "
           "     file\n2019-04-26 03:23:51     2019-04-26 03:23:51     "
           "2019-04-26 03:23:51     first\n2019-04-26 03:23:51     2019-04-26 "
           "03:23:51     2019-04-26 03:23:51     second\n"));
}