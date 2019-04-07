#include <memory>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include "infra/repository/FileUserRepository.h"

#include <iostream>

std::shared_ptr<User> FileUserRepository::get(std::string name) {
    std::string syncDirPath = syncDirPathFrom(name);
    createDirIfNotExists(syncDirPath);
    std::list<File> files = listFiles(syncDirPath);
    return std::make_shared<User>(name, files);
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

std::list<File> FileUserRepository::listFiles(std::string syncDirPath) {
    DIR* dir = opendir(syncDirPath.c_str());
    struct dirent* entry;

    std::list<File> files;
    while ((entry = readdir(dir)) != 0) {
        if (entry->d_name[0] != '.') {
            files.push_back(File(entry->d_name, timestampsFrom(entry)));
        }
    }

    closedir(dir);
    return files;
}

Timestamps FileUserRepository::timestampsFrom(struct dirent* entry) {
    struct stat st;
    stat(entry->d_name, &st);
    return Timestamps(st.st_atim.tv_sec, st.st_mtim.tv_sec, st.st_ctim.tv_sec);
}
