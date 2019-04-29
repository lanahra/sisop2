#ifndef SYSTEM_FILE_REPOSITORY_H
#define SYSTEM_FILE_REPOSITORY_H

#include <stdexcept>
#include <string>
#include "server/FileRepository.h"
#include "server/Clock.h"

class SystemFileRepository : public FileRepository {
    std::string PREFIX = "sync_dir_";
    std::string DELETED = ".removed_files";
    const mode_t PERMISSION_MODE = 0755;

    Clock& clock;

    void makeDirIfNotExist(std::string dir);
    bool fileExists(std::string path);
    void makeDir(std::string dir);
    void saveTimestamps(std::string path, Timestamps timestamps);
    Timestamps timestampsFrom(std::string filename);
    std::string bodyFrom(std::string path);
    std::list<FileEntry> readDirEntries(std::string dir);
    void recordRemovedEntry(std::string dir, std::string filename);

  public:
    SystemFileRepository(Clock& clock) : clock(clock){};
    void save(std::string dir, File file);
    void saveLocal(File file);
    File get(std::string dir, std::string filename);
    File getLocal(std::string fileAbsolutePath);
    std::list<FileEntry> getEntries(std::string dir);
    void remove(std::string dir, std::string filename) override;
};

#endif
