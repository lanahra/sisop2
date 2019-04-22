#ifndef MOCK_FILE_REPOSITORY_H
#define MOCK_FILE_REPOSITORY_H

#include <gmock/gmock.h>
#include "server/FileRepository.h"

class MockFileRepository : public FileRepository {
  public:
    MOCK_METHOD2(save, void(std::string, File));
    MOCK_METHOD2(get, File(std::string, std::string));
    MOCK_METHOD1(getEntries, std::list<FileEntry>(std::string));
    MOCK_METHOD2(remove, void(std::string, std::string));
};

#endif
