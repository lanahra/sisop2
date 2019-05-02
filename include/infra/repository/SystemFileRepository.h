#ifndef SYSTEM_FILE_REPOSITORY_H
#define SYSTEM_FILE_REPOSITORY_H

#include <stdexcept>
#include <string>
#include "server/FileRepository.h"
#include "server/Clock.h"

class SystemFileRepository : public FileRepository {
    std::string PREFIX = "sync_dir_";
    std::string STATUS_FILE = ".status";
    const mode_t PERMISSION_MODE = 0755;

    void makeDirIfNotExist(std::string dir);
    bool fileExists(std::string path);
    void makeDir(std::string dir);
    void saveTimestamps(std::string path, Timestamps timestamps);
    Timestamps timestampsFrom(std::string filename);
    std::string bodyFrom(std::string path);
    std::list<FileEntry> readDirEntries(std::string dir);
    std::list<FileEntry> readStatusEntries(std::string path);

  public:
    void save(std::string dir, File file);
    void saveLocal(File file);
    File get(std::string dir, std::string filename);
    File getLocal(std::string fileAbsolutePath);
    void remove(std::string dir, std::string filename) override;
    std::list<FileEntry> getEntries(std::string dir) override;
    std::list<FileEntry> getStatus(std::string dir) override;
    void saveStatus(std::string dir, std::list<FileEntry> entries) override;
};

#endif
