#include "application/DefaultUserService.h"

std::list<FileEntry> DefaultUserService::listFileEntries(std::string name) {
    User user = userFactory.createUser(name);
    return user.listEntries();
}
