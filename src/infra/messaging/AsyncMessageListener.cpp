#include "infra/messaging/AsyncMessageListener.h"

#include <thread>

void AsyncMessageListener::listen() {
    std::thread t(
        [](std::unique_ptr<MessageListener> listener) { listener->listen(); },
        std::move(listener));
    t.detach();
}
