#ifndef USER_BUILDER_H
#define USER_BUILDER_H

#include <string>
#include <list>
#include "server/User.h"

class UserBuilder {
    std::string name = "a user";

  public:
    User build() {
        return User(name);
    }
};

#endif
