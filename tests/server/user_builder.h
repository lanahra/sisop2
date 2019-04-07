#ifndef USER_BUILDER_H
#define USER_BUILDER_H

#include <string>
#include <list>
#include <server/user.h>

class UserBuilder {
    std::string name = "a user";
    std::list<File> files;

  public:
    User build() {
        return User(name, files);
    }
};

#endif
