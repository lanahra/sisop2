#ifndef SISOP2_LISTSERVERDIRECTORIESREQUEST_H
#define SISOP2_LISTSERVERDIRECTORIESREQUEST_H

class ListServerDirectoriesRequest {
    std::string address;
    int port;

  public:
    ListServerDirectoriesRequest(){};
    ListServerDirectoriesRequest(std::string address, int port)
            : address(address), port(port){};

    std::string getAddress() {
        return address;
    }

    int getPort() {
        return port;
    }

    friend bool operator==(const ListServerDirectoriesRequest& self,
                           const ListServerDirectoriesRequest& other) {
        return self.address == other.address && self.port == other.port;
    }

    friend std::ostream& operator<<(std::ostream& out,
                                    const ListServerDirectoriesRequest& self) {
        out << self.address.size() << ",";
        out << self.address << ",";
        out << self.port;

        return out;
    }

    friend std::istream& operator>>(std::istream& in, ListServerDirectoriesRequest& self) {
        size_t address_size;
        in >> address_size;
        in.ignore(1, ',');
        self.address.resize(address_size);
        in.read(&self.address[0], address_size);
        in.ignore(1, ',');
        size_t port;
        in >> port;
        self.port = static_cast<int>(port);

        return in;
    }
};

#endif
