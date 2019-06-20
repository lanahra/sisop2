#ifndef DOWNLOAD_FILE_RESPONSE_H
#define DOWNLOAD_FILE_RESPONSE_H

#include <iostream>
#include "server/File.h"

class DownloadFileResponse {
    std::string username;
    bool found;
    File file;

  public:
    DownloadFileResponse(){};
    DownloadFileResponse(std::string username) : username(username),
                                                 found(false){};
    DownloadFileResponse(std::string username, File file) : username(username),
                                                            found(true),
                                                            file(file){};

    bool hasFile() {
        return found;
    }

    File getFile() {
        return file;
    }

    std::string getUsername() {
        return username;
    }

    friend std::ostream& operator<<(std::ostream& out,
                                    const DownloadFileResponse& self) {
        out << self.username.size()
            << ','
            << self.username
            << ',';

        out << self.found;
        if (self.found) {
            out << ',' << self.file;
        }
        return out;
    }

    friend std::istream& operator>>(std::istream& in,
                                    DownloadFileResponse& self) {
        size_t size;
        in >> size;
        in.ignore(1, ',');
        self.username.resize(size);
        in.read(&self.username[0], size);
        in.ignore(1, ',');

        in >> self.found;
        if (self.found) {
            in.ignore(1, ',');
            in >> self.file;
        }
        return in;
    }
};

#endif
