#ifndef FILE_H
#define FILE_H

#include <string>
#include <iostream>
#include "Timestamps.h"

class File {
    std::string name;
    Timestamps timestamps;
    std::string body;

  public:
    File(){};
    File(std::string name);
    File(std::string name, Timestamps timestamps);
    File(std::string name, Timestamps timestamps, std::string body);

    std::string getName();
    Timestamps getTimestamps();
    std::string getBody();

    friend bool operator==(const File& self, const File& other) {
        return self.name == other.name && self.timestamps == other.timestamps
            && self.body == other.body;
    }

    friend std::ostream& operator<<(std::ostream& out, const File& self) {
        return out << self.name.size() << ',' << self.name << ','
                   << self.timestamps << ',' << self.body.size() << ','
                   << self.body;
    }

    friend std::istream& operator>>(std::istream& in, File& self) {
        std::string::size_type size;
        in >> size;
        in.ignore(1, ',');
        self.name.resize(size);
        in.read(&self.name[0], size);
        in.ignore(1, ',');
        in >> self.timestamps;
        in.ignore(1, ',');
        in >> size;
        in.ignore(1, ',');
        self.body.resize(size);
        in.read(&self.body[0], size);
        return in;
    }
};

#endif
