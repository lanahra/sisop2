#include <gmock/gmock.h>
#include <map>
#include <string>
#include <memory>
#include "MockSocket.h"
#include "MockListenerLoop.h"
#include "MockMessageHandler.h"
#include "infra/messaging/MessageHandler.h"
#include "infra/messaging/BlockingMessageListener.h"

using ::testing::InSequence;
using ::testing::Return;
using ::testing::Ref;

TEST(BlockingMessageListenerTest, ReadsMessageFromSocket) {
    std::shared_ptr<MockSocket> socket = std::make_shared<MockSocket>();
    {
        InSequence s;
        EXPECT_CALL(*socket, readInt()).WillOnce(Return(18));
        EXPECT_CALL(*socket, read(18)).WillOnce(Return("9,operation,4,8888"));
    }

    MockListenerLoop listenerLoop;
    EXPECT_CALL(listenerLoop, isOpen())
        .WillOnce(Return(true))
        .WillOnce(Return(false));

    std::shared_ptr<MockMessageHandler> handler
        = std::make_shared<MockMessageHandler>();
    EXPECT_CALL(*handler, handle("8888", Ref(*socket)));

    std::map<std::string, std::shared_ptr<MessageHandler>> handlers;
    handlers["operation"] = handler;

    BlockingMessageListener listener(socket, listenerLoop, handlers);
    listener.listen();
}
