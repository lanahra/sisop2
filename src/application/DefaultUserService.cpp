#include "application/DefaultUserService.h"
#include <infra/repository/FileNotFoundException.h>

#include <iostream>

File DefaultUserService::getFile(std::string username, std::string filename) {
    keyLock.lockRead(username);
    auto user = userRepository.getUser(username);
    File file = user->getFile(filename);
    keyLock.unlockRead(username);
    return file;
}

std::list<FileEntry> DefaultUserService::listFileEntries(std::string username) {
    keyLock.lockRead(username);
    auto user = userRepository.getUser(username);
    std::list<FileEntry> entries = user->listEntries();
    keyLock.unlockRead(username);
    return entries;
}

void DefaultUserService::removeFile(std::string username,
                                    std::string filename) {
    keyLock.lockWrite(username);
    try {
        tryToRemoveFile(username, filename);
    } catch (const FileNotFoundException& e) {
        std::clog << e.what() << std::endl;
    }
    keyLock.unlockWrite(username);
}

void DefaultUserService::tryToRemoveFile(std::string username,
                                         std::string filename) {
    auto user = userRepository.getUser(username);
    user->removeFile(filename);
}

void DefaultUserService::saveFile(std::string username, File file) {
    keyLock.lockWrite(username);
    auto user = userRepository.getUser(username);
    user->saveFile(file);
    keyLock.unlockWrite(username);
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
