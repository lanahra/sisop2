#ifndef DEFAULT_USER_SERVICE_H
#define DEFAULT_USER_SERVICE_H

#include "UserFactory.h"
#include "UserService.h"

class DefaultUserService : public UserService {
    UserFactory& userFactory;
    FileRepository& repository;

    void tryToRemoveFile(std::string username, std::string filename);

  public:
    DefaultUserService(UserFactory& userFactory, FileRepository& repository)
        : userFactory(userFactory), repository(repository){};
    File getFile(std::string username, std::string filename) override;
    std::list<FileEntry> listFileEntries(std::string username) override;
    void removeFile(std::string username, std::string filename) override;
    void saveFile(std::string username, File file) override;
    void saveLocal(File file) override;
    File getLocal(std::string path);
};

#endif
