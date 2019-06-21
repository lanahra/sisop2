#include <gmock/gmock-matchers.h>
#include <server/ReplicaManagers.h>
#include <infra/messaging/TcpSocket.h>

using ::testing::Eq;

TEST(ReplicaManagersTest, AddSocket) {
    ReplicaManagers replicaManagers = ReplicaManagers();
    std::shared_ptr<TcpSocket> aSocket = std::make_shared<TcpSocket>(123);
    EXPECT_THAT(replicaManagers.getSockets().size(), Eq(0));
    replicaManagers.addSocket(aSocket);
    EXPECT_THAT(replicaManagers.getSockets().size(), Eq(1));
}