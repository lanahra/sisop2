#ifndef USER_REPOSITORY_H
#define USER_REPOSITORY_H

#include <string>
#include <memory>
#include "DefaultUser.h"

class UserRepository {
  public:
    virtual std::unique_ptr<User> getUser(std::string name) = 0;
};

#endif