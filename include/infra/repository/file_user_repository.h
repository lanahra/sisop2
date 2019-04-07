#ifndef FILE_USER_REPOSITORY_H
#define FILE_USER_REPOSITORY_H

#include <string>
#include <memory>
#include "server/user_repository.h"

class FileUserRepository : public UserRepository {
    const std::string SYNC_DIR_PREFIX = "sync_dir_";
    const mode_t PERMISSION_MODE = 777;

    std::string syncDirPathFrom(std::string name);
    void createDirIfNotExists(std::string syncDirPath);

  public:
    std::shared_ptr<User> get(std::string name);
};

#endif
