#include <gmock/gmock.h>
#include "MockSocket.h"
#include "MockListenerLoop.h"
#include "infra/messaging/ConnectionListener.h"

using ::testing::Return;
using ::testing::InSequence;

TEST(ConnectionListenerTest, OpensSocketAndAcceptsNewConnections) {
    MockSocket socket;
    {
        InSequence s;
        EXPECT_CALL(socket, listen(8888));
        EXPECT_CALL(socket, accept());
    }

    MockListenerLoop listenerLoop;
    EXPECT_CALL(listenerLoop, isOpen())
        .WillOnce(Return(true))
        .WillOnce(Return(false));

    ConnectionListener listener(socket, listenerLoop);
    listener.listen(8888);
}
