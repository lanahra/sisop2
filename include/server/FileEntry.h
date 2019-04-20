#ifndef FILE_ENTRY_H
#define FILE_ENTRY_H

#include <iostream>
#include "server/Timestamps.h"

class FileEntry {
    std::string name;
    Timestamps timestamps;

  public:
    FileEntry(){};
    FileEntry(std::string name, Timestamps timestamps)
        : name(name), timestamps(timestamps){};

    std::string getName() const {
        return name;
    }

    friend bool operator==(const FileEntry& self, const FileEntry& other) {
        return self.name == other.name && self.timestamps == other.timestamps;
    }

    friend std::ostream& operator<<(std::ostream& out, const FileEntry& self) {
        return out << self.name.size() << ',' << self.name << ','
                   << self.timestamps;
    }

    friend std::istream& operator>>(std::istream& in, FileEntry& self) {
        std::string::size_type size;
        in >> size;
        in.ignore(1, ',');
        self.name.resize(size);
        in.read(&self.name[0], size);
        in.ignore(1, ',');
        in >> self.timestamps;
        return in;
    };
};

#endif
