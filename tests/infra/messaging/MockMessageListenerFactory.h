#ifndef MOCK_MESSAGE_LISTENER_FACTORY_H
#define MOCK_MESSAGE_LISTENER_FACTORY_H

#include <memory>
#include "infra/messaging/MessageListenerFactory.h"

class MockMessageListenerFactory : public MessageListenerFactory {
  public:
    MOCK_METHOD1(listenerFor,
                 std::unique_ptr<MessageListener>(std::shared_ptr<Socket>));
};

#endif
