#ifndef FILE_REPOSITORY_H
#define FILE_REPOSITORY_H

#include <list>
#include <vector>
#include "File.h"
#include "FileEntry.h"

class FileRepository {
  public:
    FileRepository() = default;
    virtual ~FileRepository() = default;

    virtual void save(std::string dir, File file) = 0;
    virtual void saveLocal(File file) = 0;
    virtual File get(std::string dir, std::string filename) = 0;
    virtual File getLocal(std::string path) = 0;
    virtual void remove(std::string dir, std::string filename) = 0;
    virtual std::list<FileEntry> getEntries(std::string dir) = 0;
    virtual std::list<FileEntry> getStatus(std::string dir) = 0;
    virtual void saveStatus(std::string dir, std::list<FileEntry> entries) = 0;
    virtual std::vector<std::string> getUsernamesFromSyncDirectories() = 0;
};

#endif
