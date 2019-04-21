#ifndef DEFAULT_USER_SERVICE_H
#define DEFAULT_USER_SERVICE_H

#include "UserService.h"
#include "UserFactory.h"

class DefaultUserService : public UserService {
    UserFactory& userFactory;

  public:
    DefaultUserService(UserFactory& userFactory) : userFactory(userFactory){};
    File getFile(std::string username, std::string filename) override;
    std::list<FileEntry> listFileEntries(std::string username) override;
};

#endif
