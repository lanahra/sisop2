#ifndef MOCK_USER_REPOSITORY_H
#define MOCK_USER_REPOSITORY_H

#include <gmock/gmock.h>
#include "server/UserRepository.h"

class MockUserRepository : public UserRepository {
  public:
    MOCK_METHOD1(getUser, std::unique_ptr<User>(std::string));
};

#endif