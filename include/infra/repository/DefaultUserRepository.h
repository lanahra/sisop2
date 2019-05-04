#ifndef DEFAULT_USER_REPOSITORY_H
#define DEFAULT_USER_REPOSITORY_H

#include "server/UserRepository.h"

class DefaultUserRepository : public UserRepository {
    FileRepository& fileRepository;

  public:
    DefaultUserRepository(FileRepository& fileRepository)
        : fileRepository(fileRepository){};

    std::unique_ptr<User> getUser(std::string name) override;
};

#endif