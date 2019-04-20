#ifndef DEFAULT_USER_SERVICE_H
#define DEFAULT_USER_SERVICE_H

#include "UserService.h"
#include "UserFactory.h"

class DefaultUserService : public UserService {
    UserFactory& userFactory;

  public:
    DefaultUserService(UserFactory& userFactory) : userFactory(userFactory){};
    std::list<FileEntry> listFileEntries(std::string name) override;
};

#endif
