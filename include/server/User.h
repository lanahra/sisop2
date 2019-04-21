#ifndef USER_H
#define USER_H

#include <string>
#include <list>
#include <stdexcept>
#include "FileRepository.h"
#include "FileEntry.h"

class User {
    std::string name;
    FileRepository& fileRepository;

  public:
    User(std::string name, FileRepository& fileRepository)
        : name(name), fileRepository(fileRepository){};

    File getFile(std::string filename);
    std::list<FileEntry> listEntries();
};

#endif
