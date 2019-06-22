#ifndef SISOP2_MOCKREPLICAMANAGERS_H
#define SISOP2_MOCKREPLICAMANAGERS_H

#include <gmock/gmock.h>
#include "server/ReplicaManagers.h"
#include <infra/messaging/Message.h>


class MockReplicaManagers : public ReplicaManagers{
  public:
    MOCK_METHOD1(addSocket, void(std::shared_ptr<Socket> socket));
    MOCK_METHOD0(getSockets, std::list<std::shared_ptr<Socket>>());
    MOCK_METHOD1(broadcast, void(Message));
};

#endif
