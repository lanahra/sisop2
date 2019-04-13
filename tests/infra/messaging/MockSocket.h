#include <gmock/gmock.h>
#include "infra/messaging/Socket.h"

class MockSocket : public Socket {
  public:
    MOCK_METHOD1(listen, void(int));
    MOCK_METHOD0(accept, std::shared_ptr<Socket>());
    MOCK_METHOD2(connect, void(std::string, int));
};
