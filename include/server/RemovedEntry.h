#ifndef REMOVED_ENTRY_H
#define REMOVED_ENTRY_H

class RemovedEntry {
    std::string name;
    std::time_t removed;

  public:
    RemovedEntry(std::string name, std::time_t removed)
        : name(name), removed(removed){};

    friend std::ostream& operator<<(std::ostream& out,
                                    const RemovedEntry& self) {
        return out << self.name.size() << ',' << self.name << ','
                   << self.removed;
    }
};

#endif