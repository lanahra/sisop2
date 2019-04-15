#include <gmock/gmock.h>
#include "MockSocket.h"
#include "MockListenerLoop.h"
#include "MockMessageListenerFactory.h"
#include "MockMessageListener.h"
#include "infra/messaging/ConnectionListener.h"

using ::testing::Return;
using ::testing::ByMove;
using ::testing::InSequence;

TEST(ConnectionListenerTest, OpensSocketAndAcceptsNewConnections) {
    MockSocket socket;
    std::shared_ptr<Socket> client = std::make_shared<MockSocket>();
    {
        InSequence s;
        EXPECT_CALL(socket, listen(8888));
        EXPECT_CALL(socket, accept()).WillOnce(Return(client));
    }

    MockListenerLoop listenerLoop;
    EXPECT_CALL(listenerLoop, isOpen())
        .WillOnce(Return(true))
        .WillOnce(Return(false));

    auto messageListener
        = std::unique_ptr<MockMessageListener>(new MockMessageListener());
    EXPECT_CALL(*messageListener, listen());

    MockMessageListenerFactory factory;
    EXPECT_CALL(factory, listenerFor(client))
        .WillOnce(Return(ByMove(std::move(messageListener))));

    ConnectionListener listener(socket, listenerLoop, factory);
    listener.listen(8888);
}
