#include <gmock/gmock.h>
#include <map>
#include <string>
#include <memory>
#include "MockMessageStreamer.h"
#include "MockListenerLoop.h"
#include "MockMessageHandler.h"
#include "infra/messaging/MessageHandler.h"
#include "infra/messaging/BlockingMessageListener.h"
#include "infra/messaging/SocketException.h"

using ::testing::InSequence;
using ::testing::Return;
using ::testing::Throw;
using ::testing::Ref;

TEST(BlockingMessageListenerTest, ReadsMessageFromSocket) {
    std::shared_ptr<MockMessageStreamer> messageStreamer
        = std::make_shared<MockMessageStreamer>();

    Message message("operation", "8888");
    EXPECT_CALL(*messageStreamer, receive()).WillOnce(Return(message));

    MockListenerLoop listenerLoop;
    EXPECT_CALL(listenerLoop, isOpen())
        .WillOnce(Return(true))
        .WillOnce(Return(false));

    std::shared_ptr<MockMessageHandler> handler
        = std::make_shared<MockMessageHandler>();
    EXPECT_CALL(*handler, handle(message, Ref(*messageStreamer)));

    std::map<std::string, std::shared_ptr<MessageHandler>> handlers;
    handlers["operation"] = handler;

    BlockingMessageListener listener(messageStreamer, listenerLoop, handlers);
    listener.listen();
}

TEST(BlockingMessageListenerTest, CatchesSocketException) {
    std::shared_ptr<MockMessageStreamer> messageStreamer
        = std::make_shared<MockMessageStreamer>();
    EXPECT_CALL(*messageStreamer, receive())
        .WillRepeatedly(Throw(SocketException("error")));

    MockListenerLoop listenerLoop;
    EXPECT_CALL(listenerLoop, isOpen()).WillRepeatedly(Return(true));

    std::map<std::string, std::shared_ptr<MessageHandler>> handlers;
    BlockingMessageListener listener(messageStreamer, listenerLoop, handlers);

    try {
        listener.listen();
    } catch (SocketException e) {
        FAIL();
    }
}
