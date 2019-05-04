#include "infra/repository/DefaultUserRepository.h"

#include "server/DefaultUser.h"

std::unique_ptr<User> DefaultUserRepository::getUser(std::string name) {
    return std::unique_ptr<User>(new DefaultUser(name, fileRepository));
}
