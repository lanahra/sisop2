#ifndef FILE_NOT_FOUND_EXCEPTION_H
#define FILE_NOT_FOUND_EXCEPTION_H

#include <stdexcept>

class FileNotFoundException : public std::runtime_error {
  public:
    FileNotFoundException(std::string filename)
        : std::runtime_error("File does not exist: " + filename){};
};

#endif
