#ifndef DEFAULT_USER_SERVICE_H
#define DEFAULT_USER_SERVICE_H

#include "UserService.h"
#include "server/UserRepository.h"

class DefaultUserService : public UserService {
    UserRepository& userRepository;
    FileRepository& fileRepository;

    void tryToRemoveFile(std::string username, std::string filename);

  public:
    DefaultUserService(UserRepository& userRepository,
                       FileRepository& fileRepository)
        : userRepository(userRepository), fileRepository(fileRepository){};
    File getFile(std::string username, std::string filename) override;
    std::list<FileEntry> listFileEntries(std::string username) override;
    void removeFile(std::string username, std::string filename) override;
    void saveLocal(File file) override;
    std::list<SyncOperation> syncUser(std::string username,
                                      std::list<FileEntry> remote) override;
};

#endif
