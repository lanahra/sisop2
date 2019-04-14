#include <gmock/gmock.h>
#include "MockSocket.h"
#include "MockListenerLoop.h"
#include "infra/messaging/BlockingMessageListener.h"

using ::testing::InSequence;
using ::testing::Return;

TEST(BlockingMessageListenerTest, ReadsMessageFromSocket) {
    MockSocket socket;
    {
        InSequence s;
        EXPECT_CALL(socket, readInt()).WillOnce(Return(4));
        EXPECT_CALL(socket, read(4));
    }

    MockListenerLoop listenerLoop;
    EXPECT_CALL(listenerLoop, isOpen())
        .WillOnce(Return(true))
        .WillOnce(Return(false));

    BlockingMessageListener listener(socket, listenerLoop);
    listener.listen();
}
