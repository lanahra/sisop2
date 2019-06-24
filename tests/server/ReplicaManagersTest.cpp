#include <gmock/gmock-matchers.h>
#include <server/ReplicaManagers.h>
#include <infra/messaging/TcpSocket.h>

using ::testing::Eq;

TEST(ReplicaManagersTest, AddSocket) {
    ReplicaManagers replicaManagers = ReplicaManagers(true);
    std::shared_ptr<TcpSocket> aSocket = std::make_shared<TcpSocket>(123);
    EXPECT_THAT(replicaManagers.getSockets().size(), Eq(0));
    replicaManagers.addSocket(aSocket);
    EXPECT_THAT(replicaManagers.getSockets().size(), Eq(1));
}

TEST(ReplicaManagersTest, AddServerDescription) {
    ReplicaManagers replicaManagers = ReplicaManagers();
    replicaManagers.addBackupServerDescription("127.0.0.1", 45120);
    struct ServerDescription serverDescription;
    serverDescription = replicaManagers.getBackupsDescriptions().front();

    EXPECT_THAT(serverDescription.address, Eq("127.0.0.1"));
    EXPECT_THAT(serverDescription.port, Eq(45120));
}