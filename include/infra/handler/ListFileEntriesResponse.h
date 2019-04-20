#ifndef LIST_FILE_ENTRIES_RESPONSE_H
#define LIST_FILE_ENTRIES_RESPONSE_H

#include <list>
#include <ostream>
#include "server/FileEntry.h"

class ListFileEntriesResponse {
    std::list<FileEntry> entries;

  public:
    ListFileEntriesResponse(){};
    ListFileEntriesResponse(std::list<FileEntry> entries) : entries(entries){};

    std::list<FileEntry> getEntries() {
        return entries;
    }

    friend std::ostream& operator<<(std::ostream& out,
                                    const ListFileEntriesResponse& self) {
        out << self.entries.size();
        for (FileEntry entry : self.entries) {
            out << ',' << entry;
        }
        return out;
    }

    friend std::istream& operator>>(std::istream& in,
                                    ListFileEntriesResponse& self) {
        size_t size;
        in >> size;
        for (size_t i = 0; i < size; i++) {
            in.ignore(1, ',');
            FileEntry entry;
            in >> entry;
            self.entries.push_back(entry);
        }
        return in;
    }
};

#endif
