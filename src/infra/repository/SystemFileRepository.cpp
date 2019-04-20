#include "infra/repository/SystemFileRepository.h"
#include "infra/repository/FileNotFoundException.h"

#include <sys/stat.h>
#include <fstream>
#include <streambuf>
#include <dirent.h>

void SystemFileRepository::save(std::string dir, File file) {
    std::string syncDir(PREFIX + dir);
    makeDirIfNotExist(syncDir);
    std::ofstream fileStream(syncDir + '/' + file.getName());
    fileStream << file.getBody();
    fileStream.close();
}

void SystemFileRepository::makeDirIfNotExist(std::string dir) {
    if (!dirExists(dir)) {
        makeDir(dir);
    }
}

bool SystemFileRepository::dirExists(std::string dir) {
    struct stat st;
    return stat(dir.c_str(), &st) == 0;
}

void SystemFileRepository::makeDir(std::string dir) {
    mkdir(dir.c_str(), PERMISSION_MODE);
}

File SystemFileRepository::get(std::string dir, std::string filename) {
    std::string path(PREFIX + dir + '/' + filename);

    struct stat st;
    if (stat(path.c_str(), &st) == 0) {
        return File(filename, timestampsFrom(path), bodyFrom(path));
    } else {
        throw FileNotFoundException(path);
    }
}

Timestamps SystemFileRepository::timestampsFrom(std::string filename) {
    struct stat st;
    if (stat(filename.c_str(), &st) != 0) {
        throw FileNotFoundException(filename);
    }
    return Timestamps(st.st_atim.tv_sec, st.st_mtim.tv_sec, st.st_ctim.tv_sec);
}

std::string SystemFileRepository::bodyFrom(std::string path) {
    std::ifstream fileStream(path);
    return std::string((std::istreambuf_iterator<char>(fileStream)),
                       std::istreambuf_iterator<char>());
}

std::list<FileEntry> SystemFileRepository::getEntries(std::string dir) {
    std::string syncDir(PREFIX + dir);
    if (dirExists(syncDir)) {
        return readDirEntries(syncDir);
    } else {
        return {};
    }
}

std::list<FileEntry> SystemFileRepository::readDirEntries(std::string dir) {
    DIR* openDir = opendir(dir.c_str());
    struct dirent* entry;

    std::list<FileEntry> entries;
    while ((entry = readdir(openDir)) != 0) {
        std::string file(entry->d_name);
        std::string path(dir + '/' + file);
        if (file[0] != '.') {
            entries.push_back(FileEntry(file, timestampsFrom(path)));
        }
    }

    closedir(openDir);
    return entries;
}
