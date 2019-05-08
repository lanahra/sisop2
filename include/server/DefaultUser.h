#ifndef DEFAULT_USER_H
#define DEFAULT_USER_H

#include "User.h"
#include "FileRepository.h"

class DefaultUser : public User {
    std::string name;
    FileRepository& fileRepository;

    bool contains(std::list<FileEntry> entries, FileEntry entry);
    FileEntry findEntry(std::list<FileEntry> entries, FileEntry entry);

  public:
    DefaultUser(std::string name, FileRepository& fileRepository)
        : name(name), fileRepository(fileRepository){};

    File getFile(std::string filename);
    std::list<FileEntry> listEntries();
    void removeFile(std::string filename);
    void saveFile(File file) override;
    std::list<SyncOperation> sync(std::list<FileEntry> remote);
};

#endif
