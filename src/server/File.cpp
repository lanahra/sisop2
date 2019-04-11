#include "server/File.h"

File::File(std::string name, Timestamps timestamps, std::string body)
    : name(name), timestamps(timestamps), body(body) {
}

std::string File::getName() {
    return name;
}

std::string File::getBody() {
    return body;
}
