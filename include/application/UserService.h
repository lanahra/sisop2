#ifndef USER_SERVICE_H
#define USER_SERVICE_H

#include <list>
#include "server/File.h"
#include "server/FileEntry.h"

class UserService {
  public:
    virtual ~UserService() = default;
    virtual File getFile(std::string username, std::string filename) = 0;
    virtual std::list<FileEntry> listFileEntries(std::string username) = 0;
    virtual void removeFile(std::string username, std::string filename) = 0;
};

#endif