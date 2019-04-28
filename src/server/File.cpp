#include "server/File.h"

File::File(std::string name, Timestamps timestamps, std::string body)
    : name(name), timestamps(timestamps), body(body) {
}

std::string File::getName() {
    return name;
}

Timestamps File::getTimestamps() {
    return timestamps;
}

std::string File::getBody() {
    return body;
}
