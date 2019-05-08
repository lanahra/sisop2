#ifndef DEFAULT_USER_SERVICE_H
#define DEFAULT_USER_SERVICE_H

#include "UserService.h"
#include "KeyLock.h"
#include "server/UserRepository.h"

class DefaultUserService : public UserService {
    UserRepository& userRepository;
    FileRepository& fileRepository;
    KeyLock& keyLock;

    void tryToRemoveFile(std::string username, std::string filename);

  public:
    DefaultUserService(UserRepository& userRepository,
                       FileRepository& fileRepository,
                       KeyLock& keyLock)
        : userRepository(userRepository),
          fileRepository(fileRepository),
          keyLock(keyLock){};
    File getFile(std::string username, std::string filename) override;
    std::list<FileEntry> listFileEntries(std::string username) override;
    void removeFile(std::string username, std::string filename) override;
    void saveFile(std::string username, File file) override;
    void saveLocal(File file) override;
    File getLocal(std::string path);
    std::list<SyncOperation> syncUser(std::string username,
                                      std::list<FileEntry> remote) override;
};

#endif
