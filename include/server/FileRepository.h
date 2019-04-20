#ifndef FILE_REPOSITORY_H
#define FILE_REPOSITORY_H

#include <list>
#include "File.h"
#include "FileEntry.h"

class FileRepository {
  public:
    FileRepository() = default;
    virtual ~FileRepository() = default;

    virtual void save(std::string dir, File file) = 0;
    virtual File get(std::string dir, std::string filename) = 0;
    virtual std::list<FileEntry> getEntries(std::string dir) = 0;
};

#endif
