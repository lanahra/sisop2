#ifndef DOWNLOAD_FILE_REQUEST_H
#define DOWNLOAD_FILE_REQUEST_H

#include <string>
#include <iostream>

class DownloadFileRequest {
    std::string username;
    std::string filename;

  public:
    DownloadFileRequest() = default;
    DownloadFileRequest(std::string username, std::string filename)
        : username(username), filename(filename){};

    std::string getUsername() {
        return username;
    }

    std::string getFilename() {
        return filename;
    }

    friend bool operator==(const DownloadFileRequest& self,
                           const DownloadFileRequest& other) {
        return self.username == other.username
            && self.filename == self.filename;
    }

    friend std::ostream& operator<<(std::ostream& out,
                                    const DownloadFileRequest& self) {
        return out << self.username.size() << ',' << self.username << ','
                   << self.filename.size() << ',' << self.filename;
    }

    friend std::istream& operator>>(std::istream& in,
                                    DownloadFileRequest& self) {
        size_t size;
        in >> size;
        in.ignore(1, ',');
        self.username.resize(size);
        in.read(&self.username[0], size);
        in.ignore(1, ',');
        in >> size;
        in.ignore(1, ',');
        self.filename.resize(size);
        in.read(&self.filename[0], size);
        return in;
    }
};

#endif
