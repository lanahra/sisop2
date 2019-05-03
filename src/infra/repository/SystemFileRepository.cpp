#include "infra/repository/SystemFileRepository.h"

#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <utime.h>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <vector>
#include <set>
#include <sstream>
#include "infra/repository/FileNotFoundException.h"
#include "server/RemovedEntry.h"


void SystemFileRepository::save(std::string dir, File file) {
    std::string syncDir(PREFIX + dir);
    makeDirIfNotExist(syncDir);
    std::string path(syncDir + '/' + file.getName());
    std::ofstream fileStream(path);
    fileStream << file.getBody();
    fileStream.close();
    saveTimestamps(path, file.getTimestamps());
}

void SystemFileRepository::makeDirIfNotExist(std::string dir) {
    if (!fileExists(dir)) {
        makeDir(dir);
    }
}

bool SystemFileRepository::fileExists(std::string path) {
    struct stat st;
    return stat(path.c_str(), &st) == 0;
}

void SystemFileRepository::makeDir(std::string dir) {
    mkdir(dir.c_str(), PERMISSION_MODE);
}

void SystemFileRepository::saveTimestamps(std::string path,
                                          Timestamps timestamps) {
    struct utimbuf times
        = {timestamps.getLastAccess(), timestamps.getLastModification()};
    utime(path.c_str(), &times);
}

void SystemFileRepository::saveLocal(File file) {
    std::ofstream fileStream(file.getName());
    fileStream << file.getBody();
    fileStream.close();
}

File SystemFileRepository::get(std::string dir, std::string filename) {
    std::string path(PREFIX + dir + '/' + filename);

    if (fileExists(path)) {
        return File(filename, timestampsFrom(path), bodyFrom(path));
    } else {
        throw FileNotFoundException(path);
    }
}

File SystemFileRepository::getLocal(std::string path) {
    if (fileExists(path)) {
        return File(fileNameFrom(path),
                    timestampsFrom(path),
                    bodyFrom(path));
    } else {
        throw FileNotFoundException(path);
    }
}

std::string SystemFileRepository::fileNameFrom(std::string path) {
    std::stringstream pathStringStream(path);
    std::string aux;
    std::vector<std::string> splitList;

    while(std::getline(pathStringStream, aux, '/'))
    {
        splitList.push_back(aux);
    }
    return std::string(splitList.back());
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

void SystemFileRepository::remove(std::string dir, std::string filename) {
    std::string path(PREFIX + dir + '/' + filename);
    if (fileExists(path)) {
        std::remove(path.c_str());
    } else {
        throw FileNotFoundException(path);
    }
}

std::list<FileEntry> SystemFileRepository::getEntries(std::string dir) {
    std::string syncDir(PREFIX + dir);
    if (fileExists(syncDir)) {
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

std::list<FileEntry> SystemFileRepository::getStatus(std::string dir) {
    std::string path(PREFIX + dir + "/" + STATUS_FILE);

    if (fileExists(path)) {
        return readStatusEntries(path);
    } else {
        return {};
    }
}

std::list<FileEntry> SystemFileRepository::readStatusEntries(std::string path) {
    std::list<FileEntry> entries;
    std::ifstream fileStream(path);

    std::string line;
    while (std::getline(fileStream, line)) {
        std::stringstream serialized(line);
        FileEntry entry;
        serialized >> entry;
        entries.push_back(entry);
    }

    return entries;
}

void SystemFileRepository::saveStatus(std::string dir,
                                      std::list<FileEntry> entries) {
    std::string path(PREFIX + dir + "/" + STATUS_FILE);

    if (!entries.empty()) {
        std::ofstream fileStream(path);
        for (FileEntry entry : entries) {
            fileStream << entry << std::endl;
        }
    }
}

