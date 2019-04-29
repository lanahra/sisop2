#ifndef SISOP2_UPLOADFILEREQUEST_H
#define SISOP2_UPLOADFILEREQUEST_H


#include <server/File.h>

class UploadFileRequest {
    std::string username;
    File file;

  public:
    UploadFileRequest() = default;
    UploadFileRequest(std::string username, File file)
    : username(username), file(file){};

    std::string getUsername() {
        return username;
    }

    File getFilename() {
        return file;
    }

    friend bool operator==(const UploadFileRequest& self,
                           const UploadFileRequest& other) {
        return self.username == other.username
               && self.file == other.file;
    }

    /*
    friend std::ostream& operator<<(std::ostream& out,
                                    const UploadFileRequest& self) {
        return out << self.username.size() << ',' << self.username << ','
                   << self.file.size() << ',' << self.file;
    }

    friend std::istream& operator>>(std::istream& in,
                                    UploadFileRequest& self) {
        size_t size;
        in >> size;
        in.ignore(1, ',');
        self.username.resize(size);
        in.read(&self.username[0], size);
        in.ignore(1, ',');
        in >> size;
        in.ignore(1, ',');
        self.file.resize(size);
        in.read(&self.file[0], size);
        return in;
    }
    */
};


#endif