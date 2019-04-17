#include <gmock/gmock.h>
#include "infra/messaging/SocketMessageStreamer.h"
#include "infra/messaging/Message.h"
#include "MockSocket.h"

using ::testing::InSequence;
using ::testing::Return;
using ::testing::Eq;

TEST(SocketMessageStreamerTest, ReceivesMessage) {
    std::shared_ptr<MockSocket> socket = std::make_shared<MockSocket>();
    {
        InSequence s;
        EXPECT_CALL(*socket, readInt()).WillOnce(Return(18));
        EXPECT_CALL(*socket, read(18)).WillOnce(Return("9,operation,4,8888"));
    }

    SocketMessageStreamer messageStreamer(socket);

    Message message = messageStreamer.receive();
    EXPECT_THAT(message.getOperation(), Eq("operation"));
    EXPECT_THAT(message.getBody(), Eq("8888"));
}

TEST(SocketMessageStreamerTest, SendsMessage) {
    std::shared_ptr<MockSocket> socket = std::make_shared<MockSocket>();
    {
        InSequence s;
        EXPECT_CALL(*socket, writeInt(18));

        std::string body("9,operation,4,8888");
        EXPECT_CALL(*socket, write(body));
    }

    Message message("operation", "8888");
    SocketMessageStreamer messageStreamer(socket);
    messageStreamer.send(message);
}
