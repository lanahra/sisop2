#ifndef MOCK_KEY_LOCK_H
#define MOCK_KEY_LOCK_H

#include <gmock/gmock.h>
#include "application/KeyLock.h"

class MockKeyLock : public KeyLock {
  public:
    MOCK_METHOD1(lockRead, void(std::string));
    MOCK_METHOD1(unlockRead, void(std::string));
    MOCK_METHOD1(lockWrite, void(std::string));
    MOCK_METHOD1(unlockWrite, void(std::string));
};

#endif