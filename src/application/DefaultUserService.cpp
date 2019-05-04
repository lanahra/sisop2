#include "application/DefaultUserService.h"
#include <infra/repository/FileNotFoundException.h>

#include <iostream>

File DefaultUserService::getFile(std::string username, std::string filename) {
    auto user = userRepository.getUser(username);
    return user->getFile(filename);
}

std::list<FileEntry> DefaultUserService::listFileEntries(std::string username) {
    auto user = userRepository.getUser(username);
    return user->listEntries();
}

void DefaultUserService::removeFile(std::string username,
                                    std::string filename) {
    try {
        tryToRemoveFile(username, filename);
    } catch (const FileNotFoundException& e) {
        std::clog << e.what() << std::endl;
    }
}

void DefaultUserService::tryToRemoveFile(std::string username,
                                         std::string filename) {
    auto user = userRepository.getUser(username);
    user->removeFile(filename);
}

void DefaultUserService::saveFile(std::string username, File file) {
    fileRepository.save(username, file);
}

void DefaultUserService::saveLocal(File file) {
    fileRepository.saveLocal(file);
}

std::list<SyncOperation> DefaultUserService::syncUser(
    std::string username,
    std::list<FileEntry> remote) {
    auto user = userRepository.getUser(username);
    return user->sync(remote);
}

File DefaultUserService::getLocal(std::string path) {
    return fileRepository.getLocal(path);
}
