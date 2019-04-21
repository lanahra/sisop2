#include "application/DefaultUserService.h"

File DefaultUserService::getFile(std::string username, std::string filename) {
    User user = userFactory.createUser(username);
    return user.getFile(filename);
}

std::list<FileEntry> DefaultUserService::listFileEntries(std::string username) {
    User user = userFactory.createUser(username);
    return user.listEntries();
}
