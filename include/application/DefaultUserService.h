#ifndef DEFAULT_USER_SERVICE_H
#define DEFAULT_USER_SERVICE_H

#include "UserFactory.h"
#include "UserService.h"

class DefaultUserService : public UserService {
    UserFactory& userFactory;

    void tryToRemoveFile(std::string username, std::string filename);

  public:
    DefaultUserService(UserFactory& userFactory) : userFactory(userFactory){};
    File getFile(std::string username, std::string filename) override;
    std::list<FileEntry> listFileEntries(std::string username) override;
    void removeFile(std::string username, std::string filename) override;
};

#endif