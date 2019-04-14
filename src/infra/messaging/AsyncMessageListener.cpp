#include "infra/messaging/AsyncMessageListener.h"

#include <thread>

void AsyncMessageListener::listen() {
    std::thread t(&MessageListener::listen, &listener);
    t.detach();
}
