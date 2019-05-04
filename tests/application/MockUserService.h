#ifndef MOCK_USER_SERVICE_H
#define MOCK_USER_SERVICE_H

#include "application/UserService.h"

class MockUserService : public UserService {
  public:
    MOCK_METHOD2(getFile, File(std::string, std::string));
    MOCK_METHOD1(listFileEntries, std::list<FileEntry>(std::string));
    MOCK_METHOD2(removeFile, void(std::string, std::string));
    MOCK_METHOD1(saveLocal, void(File));
    MOCK_METHOD2(syncUser,
                 std::list<SyncOperation>(std::string, std::list<FileEntry>));
};

#endif
