#include <gmock/gmock.h>
#include "MockMessageListener.h"
#include "infra/messaging/AsyncMessageListener.h"

#include <mutex>
#include <condition_variable>

ACTION_P3(ReturnAsync, m, cv, r) {
    std::unique_lock<std::mutex> lk(*m);
    *r = true;
    cv->notify_one();
};

TEST(AsyncMessageListenerTest, StartsListeningInAnotherThread) {
    std::mutex m;
    std::condition_variable cv;
    bool ready = false;
    auto listener
        = std::unique_ptr<MockMessageListener>(new MockMessageListener());
    EXPECT_CALL(*listener, listen()).WillOnce(ReturnAsync(&m, &cv, &ready));

    AsyncMessageListener asyncListener(std::move(listener));
    asyncListener.listen();

    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk, [&] { return ready; });
};
