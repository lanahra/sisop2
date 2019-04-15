#include "infra/messaging/AsyncMessageListenerFactory.h"
#include "infra/messaging/BlockingMessageListener.h"
#include "infra/messaging/AsyncMessageListener.h"

std::unique_ptr<MessageListener> AsyncMessageListenerFactory::listenerFor(
    std::shared_ptr<Socket> socket) {
    auto innerListener = std::unique_ptr<MessageListener>(
        new BlockingMessageListener(socket, listenerLoop, handlers));
    auto asyncListener = std::unique_ptr<MessageListener>(
        new AsyncMessageListener(std::move(innerListener)));
    return std::move(asyncListener);
}
