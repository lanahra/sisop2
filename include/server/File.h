#ifndef FILE_H
#define FILE_H

#include <string>
#include <iostream>
#include "Timestamps.h"

class File {
    std::string name;
    Timestamps timestamps;

  public:
    File(std::string name);
    File(std::string name, Timestamps timestamps);

    friend bool operator==(const File& self, const File& other) {
        return self.name == other.name;
    }

    friend std::ostream& operator<<(std::ostream& stream, const File& file) {
        return stream << "File(\"" << file.name << "\")";
    }
};

#endif
