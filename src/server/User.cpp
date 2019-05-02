#include "server/User.h"
#include <algorithm>

File User::getFile(std::string filename) {
    return fileRepository.get(name, filename);
}

std::list<FileEntry> User::listEntries() {
    return fileRepository.getEntries(name);
}

void User::removeFile(std::string filename) {
    fileRepository.remove(name, filename);
}

std::list<SyncOperation> User::sync(std::list<FileEntry> remote) {
    std::list<SyncOperation> operations;
    std::list<FileEntry> local = fileRepository.getEntries(name);
    std::list<FileEntry> status = fileRepository.getStatus(name);

    for (FileEntry entry : remote) {
        if (contains(local, entry)) {
            FileEntry localEntry = findEntry(local, entry);
            if (entry.newerThan(localEntry)) {
                operations.push_back(
                    SyncOperation(SyncOperation::DOWNLOAD, entry.getName()));
                if (!contains(status, entry)) {
                    status.push_back(entry);
                }
            }
        } else {
            if (contains(status, entry)) {
                operations.push_back(
                    SyncOperation(SyncOperation::DELETE, entry.getName()));
                status.remove_if([&](const FileEntry& e) {
                    return e.getName() == entry.getName();
                });
            } else {
                operations.push_back(
                    SyncOperation(SyncOperation::DOWNLOAD, entry.getName()));
                status.push_back(entry);
            }
        }
    }

    for (FileEntry entry : local) {
        if (contains(remote, entry)) {
            FileEntry remoteEntry = findEntry(remote, entry);
            if (entry.newerThan(remoteEntry)) {
                operations.push_back(
                    SyncOperation(SyncOperation::UPLOAD, entry.getName()));
                if (!contains(status, entry)) {
                    status.push_back(entry);
                }
            }
        } else {
            if (contains(status, entry)) {
                fileRepository.remove(name, entry.getName());
                status.remove_if([&](const FileEntry& e) {
                    return e.getName() == entry.getName();
                });
            } else {
                operations.push_back(
                    SyncOperation(SyncOperation::UPLOAD, entry.getName()));
                status.push_back(entry);
            }
        }
    }

    status.remove_if([&](const FileEntry& e) {
        return !contains(local, e) && !contains(remote, e);
    });

    fileRepository.saveStatus(name, status);
    return operations;
}

bool User::contains(std::list<FileEntry> entries, FileEntry entry) {
    return (std::find_if(entries.begin(),
                         entries.end(),
                         [&](const FileEntry& e) {
                             return e.getName() == entry.getName();
                         })
            != entries.end());
}

FileEntry User::findEntry(std::list<FileEntry> entries, FileEntry entry) {
    auto it
        = std::find_if(entries.begin(), entries.end(), [&](const FileEntry& e) {
              return e.getName() == entry.getName();
          });
    return *it;
}
