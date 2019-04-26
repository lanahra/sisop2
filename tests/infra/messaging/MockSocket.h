#ifndef MOCK_SOCKET_H
#define MOCK_SOCKET_H

#include <gmock/gmock.h>
#include "infra/messaging/Socket.h"

class MockSocket : public Socket {
  public:
    MOCK_METHOD1(listen, void(int));
    MOCK_METHOD0(accept, std::shared_ptr<Socket>());
    MOCK_METHOD2(connect, void(std::string, int));
    MOCK_METHOD0(readInt, int());
    MOCK_METHOD1(read, std::string(int));
    MOCK_METHOD1(writeInt, void(int));
    MOCK_METHOD1(write, void(std::string));
    MOCK_METHOD0(close, void());
};

#endif
