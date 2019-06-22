#ifndef MOCK_MESSAGE_STREAMER_H
#define MOCK_MESSAGE_STREAMER_H

#include <gmock/gmock.h>
#include "infra/messaging/MessageStreamer.h"
#include "infra/messaging/Message.h"

class MockMessageStreamer : public MessageStreamer {
  public:
    MOCK_METHOD0(receive, Message());
    MOCK_METHOD1(send, void(Message));
    MOCK_METHOD0(close, void());
    MOCK_METHOD0(getSocket, std::shared_ptr<Socket>());
};

#endif
