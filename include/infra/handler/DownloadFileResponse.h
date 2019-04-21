#ifndef DOWNLOAD_FILE_RESPONSE_H
#define DOWNLOAD_FILE_RESPONSE_H

#include <iostream>
#include "server/File.h"

class DownloadFileResponse {
    bool found;
    File file;

  public:
    DownloadFileResponse() : found(false){};
    DownloadFileResponse(File file) : found(true), file(file){};

    bool hasFile() {
        return found;
    }

    File getFile() {
        return file;
    }

    friend std::ostream& operator<<(std::ostream& out,
                                    const DownloadFileResponse& self) {
        out << self.found;
        if (self.found) {
            out << ',' << self.file;
        }
        return out;
    }

    friend std::istream& operator>>(std::istream& in,
                                    DownloadFileResponse& self) {
        in >> self.found;
        if (self.found) {
            in.ignore(1, ',');
            in >> self.file;
        }
        return in;
    }
};

#endif
