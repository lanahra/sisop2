#include "application/DefaultUserService.h"
#include <infra/repository/FileNotFoundException.h>

#include <iostream>

File DefaultUserService::getFile(std::string username, std::string filename) {
    User user = userFactory.createUser(username);
    return user.getFile(filename);
}

std::list<FileEntry> DefaultUserService::listFileEntries(std::string username) {
    User user = userFactory.createUser(username);
    return user.listEntries();
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
    User user = userFactory.createUser(username);
    user.removeFile(filename);
}

void DefaultUserService::saveFile(std::string username, File file){
    repository.save("", file);
}

void DefaultUserService::saveLocal(File file) {
    repository.saveLocal(file);
}

File DefaultUserService::getLocal(std::string path) {
    return repository.getLocal(path);
}
