#ifndef MOCK_USER_H
#define MOCK_USER_H

#include <gmock/gmock.h>
#include "server/User.h"

class MockUser : public User {
  public:
    MOCK_METHOD1(getFile, File(std::string));
    MOCK_METHOD0(listEntries, std::list<FileEntry>());
    MOCK_METHOD1(removeFile, void(std::string));
    MOCK_METHOD1(sync, std::list<SyncOperation>(std::list<FileEntry>));
};

#endif