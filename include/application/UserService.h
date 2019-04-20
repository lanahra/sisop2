#ifndef USER_SERVICE_H
#define USER_SERVICE_H

#include <list>
#include "server/FileEntry.h"

class UserService {
  public:
    virtual ~UserService() = default;
    virtual std::list<FileEntry> listFileEntries(std::string name) = 0;
};

#endif
