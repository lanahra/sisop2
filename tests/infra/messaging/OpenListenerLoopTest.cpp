#include <gmock/gmock.h>

#include "infra/messaging/OpenListenerLoop.h"

using ::testing::IsTrue;

TEST(OpenListenerLoopTest, ReturnsTrueForOpenLoop) {
    OpenListenerLoop listenerLoop;

    EXPECT_THAT(listenerLoop.isOpen(), IsTrue);
}
