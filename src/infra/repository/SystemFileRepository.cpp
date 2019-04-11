#include "infra/repository/SystemFileRepository.h"

#include <sys/stat.h>
#include <fstream>
#include <streambuf>

void SystemFileRepository::save(std::string dir, File file) {
    std::ofstream fileStream(dir + '/' + file.getName());
    fileStream << file.getBody();
    fileStream.close();
}

File SystemFileRepository::get(std::string dir, std::string filename) {
    std::string path(dir + '/' + filename);

    struct stat st;
    if (stat(path.c_str(), &st) == 0) {
        return File(filename, timestampsFrom(st), bodyFrom(path));
    } else {
        throw FileNotFoundException(path);
    }
}

Timestamps SystemFileRepository::timestampsFrom(struct stat st) {
    return Timestamps(st.st_atim.tv_sec, st.st_mtim.tv_sec, st.st_ctim.tv_sec);
}

std::string SystemFileRepository::bodyFrom(std::string path) {
    std::ifstream fileStream(path);
    return std::string((std::istreambuf_iterator<char>(fileStream)),
                       std::istreambuf_iterator<char>());
}
