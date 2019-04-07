#ifndef USER_REPOSITORY_H
#define USER_REPOSITORY_H

#include <string>
#include "user.h"

class UserRepository {
  public:
    UserRepository();
    virtual ~UserRepository() = default;

    virtual User get(std::string name) = 0;
}

#endif
