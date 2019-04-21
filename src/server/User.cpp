#include "server/User.h"

File User::getFile(std::string filename) {
    return fileRepository.get(name, filename);
}

std::list<FileEntry> User::listEntries() {
    return fileRepository.getEntries(name);
}
