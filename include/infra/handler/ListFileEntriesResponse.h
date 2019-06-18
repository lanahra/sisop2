#ifndef LIST_FILE_ENTRIES_RESPONSE_H
#define LIST_FILE_ENTRIES_RESPONSE_H

#include <list>
#include <ostream>
#include "server/FileEntry.h"

class ListFileEntriesResponse {
    std::string username;
    std::list<FileEntry> entries;

  public:
    ListFileEntriesResponse(){};
    ListFileEntriesResponse(std::string username, std::list<FileEntry> entries) :
                            username(username), entries(entries){};

    std::list<FileEntry> getEntries() {
        return entries;
    }

    std::string getUsername() {
        return username;
    }

    friend std::ostream& operator<<(std::ostream& out,
                                    const ListFileEntriesResponse& self) {
        out << self.username.size() << ",";
        out << self.username << ",";

        out << self.entries.size();
        for (FileEntry entry : self.entries) {
            out << ',' << entry;
        }
        return out;
    }

    friend std::istream& operator>>(std::istream& in,
                                    ListFileEntriesResponse& self) {
        size_t username_size;
        in >> username_size;
        in.ignore(1, ',');
        self.username.resize(username_size);
        in.read(&self.username[0], username_size);
        in.ignore(1, ',');

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
