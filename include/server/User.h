#ifndef USER_H
#define USER_H

#include <list>
#include <string>
#include "File.h"
#include "FileEntry.h"
#include "SyncOperation.h"

class User {
  public:
    virtual ~User() = default;
    virtual File getFile(std::string filename) = 0;
    virtual std::list<FileEntry> listEntries() = 0;
    virtual void removeFile(std::string filename) = 0;
    virtual std::list<SyncOperation> sync(std::list<FileEntry> remote) = 0;
};

#endif
