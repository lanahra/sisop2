#include <gmock/gmock.h>
#include <sstream>
#include <infra/handler/UpdateBackupsListRequest.h>
#include <server/ServerDescription.h>
#include <list>

using ::testing::Eq;

TEST(UpdateBackupsListRequestTest, SerializesRequest) {
    struct ServerDescription serverDescription;
    serverDescription.address = "127.0.0.1";
    serverDescription.port = 45120;

    struct ServerDescription secondServerDescription;
    secondServerDescription.address = "localhost";
    secondServerDescription.port = 45121;

    std::list<struct ServerDescription> backupsServerDescriptions{
        serverDescription, secondServerDescription
    };
    UpdateBackupsListRequest request(backupsServerDescriptions);

    std::stringstream serialized;
    serialized << request;

    EXPECT_THAT(serialized.str(), Eq("2,9,127.0.0.1,45120,9,localhost,45121"));
}

TEST(UpdateBackupsListRequestTest, DeserializesRequest) {
    std::stringstream serialized("2,9,127.0.0.1,45120,9,localhost,45121");
    UpdateBackupsListRequest request;
    serialized >> request;

    EXPECT_THAT(request.getBackupsDescriptions().front().address, Eq("127.0.0.1"));
    EXPECT_THAT(request.getBackupsDescriptions().front().port, Eq(45120));
    EXPECT_THAT(request.getBackupsDescriptions().back().address, Eq("localhost"));
    EXPECT_THAT(request.getBackupsDescriptions().back().port, Eq(45121));
}

