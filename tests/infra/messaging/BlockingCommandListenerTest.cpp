#include <gmock/gmock.h>
#include "MockCommandHandler.h"
#include "MockListenerLoop.h"
#include "MockMessageStreamer.h"
#include "infra/messaging/BlockingCommandListener.h"

using ::testing::ElementsAre;
using ::testing::Ref;
using ::testing::Return;

TEST(BlockingCommandListenerTest, ReadsCommandFromInput) {
    std::shared_ptr<MockMessageStreamer> messageStreamer
        = std::make_shared<MockMessageStreamer>();

    MockListenerLoop listenerLoop;
    EXPECT_CALL(listenerLoop, isOpen())
        .WillOnce(Return(true))
        .WillOnce(Return(false));

    std::shared_ptr<MockCommandHandler> handler
        = std::make_shared<MockCommandHandler>();
    EXPECT_CALL(
        *handler,
        handle(ElementsAre("command", "parameter"), Ref(*messageStreamer)));

    std::map<std::string, std::shared_ptr<CommandHandler>> handlers;
    handlers["command"] = handler;

    std::istringstream input("command parameter");
    BlockingCommandListener listener(
        input, listenerLoop, messageStreamer, handlers);
    listener.listen();
}

TEST(BlockingCommandListenerTest, IgnoresEmptyInput) {
    std::shared_ptr<MockMessageStreamer> messageStreamer
        = std::make_shared<MockMessageStreamer>();

    MockListenerLoop listenerLoop;
    EXPECT_CALL(listenerLoop, isOpen())
        .WillOnce(Return(true))
        .WillOnce(Return(false));

    std::map<std::string, std::shared_ptr<CommandHandler>> handlers;
    std::istringstream input("");

    BlockingCommandListener listener(
        input, listenerLoop, messageStreamer, handlers);
    listener.listen();
}