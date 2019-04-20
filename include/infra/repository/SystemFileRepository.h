#ifndef SYSTEM_FILE_REPOSITORY_H
#define SYSTEM_FILE_REPOSITORY_H

#include <string>
#include <stdexcept>
#include "server/FileRepository.h"

class SystemFileRepository : public FileRepository {
    std::string PREFIX = "sync_dir_";
    const mode_t PERMISSION_MODE = 0755;

    void makeDirIfNotExist(std::string dir);
    bool dirExists(std::string dir);
    void makeDir(std::string dir);
    Timestamps timestampsFrom(std::string filename);
    std::string bodyFrom(std::string path);
    std::list<FileEntry> readDirEntries(std::string dir);

  public:
    void save(std::string dir, File file);
    File get(std::string dir, std::string filename);
    std::list<FileEntry> getEntries(std::string dir);
};

#endif
