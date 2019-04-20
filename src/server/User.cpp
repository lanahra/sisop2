#include "server/User.h"

std::list<FileEntry> User::listEntries() {
    return fileRepository.getEntries(name);
}
