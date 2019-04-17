#include "infra/messaging/AsyncMessageListenerFactory.h"
#include "infra/messaging/SocketMessageStreamer.h"
#include "infra/messaging/BlockingMessageListener.h"
#include "infra/messaging/AsyncMessageListener.h"

std::unique_ptr<MessageListener> AsyncMessageListenerFactory::listenerFor(
    std::shared_ptr<Socket> socket) {
    auto messageStreamer = std::make_shared<SocketMessageStreamer>(socket);
    auto innerListener = std::unique_ptr<MessageListener>(
        new BlockingMessageListener(messageStreamer, listenerLoop, handlers));
    auto asyncListener = std::unique_ptr<MessageListener>(
        new AsyncMessageListener(std::move(innerListener)));
    return std::move(asyncListener);
}
