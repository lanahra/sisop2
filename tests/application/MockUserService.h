#ifndef MOCK_USER_SERVICE_H
#define MOCK_USER_SERVICE_H

#include "application/UserService.h"

class MockUserService : public UserService {
  public:
    MOCK_METHOD1(listFileEntries, std::list<FileEntry>(std::string));
};

#endif
