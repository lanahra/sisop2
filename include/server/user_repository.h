#ifndef USER_REPOSITORY_H
#define USER_REPOSITORY_H

#include <string>
#include <memory>
#include "user.h"

class UserRepository {
  public:
    UserRepository() = default;
    virtual ~UserRepository() = default;

    virtual std::shared_ptr<User> get(std::string name) = 0;
};

#endif
