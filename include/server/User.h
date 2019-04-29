#ifndef USER_H
#define USER_H

#include <list>
#include <stdexcept>
#include <string>
#include "FileEntry.h"
#include "FileRepository.h"
#include "SyncOperation.h"

class User {
    std::string name;
    FileRepository& fileRepository;

    bool contains(std::list<FileEntry> entries, FileEntry entry);
    FileEntry findEntry(std::list<FileEntry> entries, FileEntry entry);

  public:
    User(std::string name, FileRepository& fileRepository)
        : name(name), fileRepository(fileRepository){};

    File getFile(std::string filename);
    std::list<FileEntry> listEntries();
    void removeFile(std::string filename);
    std::list<SyncOperation> sync(std::list<FileEntry> remote);
};

#endif
