#include "server/File.h"

File::File(std::string name) : name(name), timestamps(0, 0, 0) {
    // empty constructor
}

File::File(std::string name, Timestamps timestamps)
    : name(name), timestamps(timestamps) {
    // empty constructor
}
