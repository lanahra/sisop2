#include <gmock/gmock.h>
#include "infra/messaging/SerializedMessageHandler.h"
#include "MockSocket.h"
#include "MockMessageHandler.h"

using ::testing::Ref;

TEST(SerializedMessageHandlerTest, HandlesSerializedMessage) {
    MockSocket socket;
    MockMessageHandler<int> innerHandler;
    EXPECT_CALL(innerHandler, handle(5, Ref(socket)));

    SerializedMessageHandler<int> handler(innerHandler);

    handler.handle("5", socket);
}
