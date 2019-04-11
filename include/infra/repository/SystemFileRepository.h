#ifndef SYSTEM_FILE_REPOSITORY_H
#define SYSTEM_FILE_REPOSITORY_H

#include <string>
#include <stdexcept>
#include "server/File.h"
#include "server/FileRepository.h"

class SystemFileRepository : public FileRepository {
    Timestamps timestampsFrom(struct stat st);
    std::string bodyFrom(std::string path);

  public:
    void save(std::string dir, File file);
    File get(std::string dir, std::string filename);
};

class FileNotFoundException : public std::runtime_error {
  public:
    FileNotFoundException(std::string path)
        : std::runtime_error("File not found: " + path) {
    }
};

#endif
