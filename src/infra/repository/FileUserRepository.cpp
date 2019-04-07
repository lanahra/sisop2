#include <memory>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "infra/repository/FileUserRepository.h"

std::shared_ptr<User> FileUserRepository::get(std::string name) {
    std::string syncDirPath = syncDirPathFrom(name);
    createDirIfNotExists(syncDirPath);
    return std::make_shared<User>(name);
}

std::string FileUserRepository::syncDirPathFrom(std::string name) {
    return SYNC_DIR_PREFIX + name;
}

void FileUserRepository::createDirIfNotExists(std::string syncDirPath) {
    struct stat st;
    if (stat(syncDirPath.c_str(), &st) != 0) {
        mkdir(syncDirPath.c_str(), PERMISSION_MODE);
    }
}
