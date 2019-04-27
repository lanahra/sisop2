#ifndef TIMESTAMPTS_H
#define TIMESTAMPTS_H

#include <ctime>
#include <iostream>

class Timestamps {
    std::time_t lastAccess;
    std::time_t lastModification;
    std::time_t lastChange;

  public:
    Timestamps(){};
    Timestamps(std::time_t lastAccess,
               std::time_t lastModification,
               std::time_t lastChange)
        : lastAccess(lastAccess),
          lastModification(lastModification),
          lastChange(lastChange) {
        // empty constructor
    }

    std::time_t getLastAccess() {
        return lastAccess;
    }

    std::time_t getLastModification() {
        return lastModification;
    }

    std::time_t getLastChange() {
        return lastChange;
    }

    friend bool operator==(const Timestamps& self, const Timestamps& other) {
        return self.lastAccess == other.lastAccess
            && self.lastModification == other.lastModification;
    }

    friend std::ostream& operator<<(std::ostream& out, const Timestamps& self) {
        return out << self.lastAccess << ',' << self.lastModification << ','
                   << self.lastChange;
    }

    friend std::istream& operator>>(std::istream& in, Timestamps& self) {
        in >> self.lastAccess;
        in.ignore(1, ',');
        in >> self.lastModification;
        in.ignore(1, ',');
        in >> self.lastChange;
        return in;
    }
};

#endif
