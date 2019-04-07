#ifndef FILE_USER_REPOSITORY_H
#define FILE_USER_REPOSITORY_H

#include <string>
#include <memory>
#include <dirent.h>
#include "server/UserRepository.h"

class FileUserRepository : public UserRepository {
    const std::string SYNC_DIR_PREFIX = "sync_dir_";
    const mode_t PERMISSION_MODE = 777;

    std::string syncDirPathFrom(std::string name);
    void createDirIfNotExists(std::string syncDirPath);
    std::list<File> listFiles(std::string syncDirPath);
    Timestamps timestampsFrom(struct dirent* entry);

  public:
    std::shared_ptr<User> get(std::string name);
};

#endif
