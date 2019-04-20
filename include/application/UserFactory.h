#ifndef USER_FACTORY_H
#define USER_FACTORY_H

#include "server/User.h"
#include "UserFactory.h"

class UserFactory {
    FileRepository& fileRepository;

  public:
    UserFactory(FileRepository& fileRepository)
        : fileRepository(fileRepository){};
    User createUser(std::string name) {
        return User(name, fileRepository);
    };
};

#endif
