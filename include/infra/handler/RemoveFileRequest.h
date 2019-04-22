#ifndef REMOVE_FILE_REQUEST_H
#define REMOVE_FILE_REQUEST_H

#include <string>
#include <iostream>

class RemoveFileRequest {
    std::string username;
    std::string filename;

  public:
    RemoveFileRequest() = default;
    RemoveFileRequest(std::string username, std::string filename)
    : username(username), filename(filename){};

    std::string getUsername() {
        return username;
    }

    std::string getFilename() {
        return filename;
    }

    friend bool operator==(const RemoveFileRequest& self,
                           const RemoveFileRequest& other) {
        return self.username == other.username
               && self.filename == other.filename;
    }

    friend std::ostream& operator<<(std::ostream& out,
                                    const RemoveFileRequest& self) {
        return out << self.username.size() << ',' << self.username << ','
                   << self.filename.size() << ',' << self.filename;
    }

    friend std::istream& operator>>(std::istream& in,
                                    RemoveFileRequest& self) {
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