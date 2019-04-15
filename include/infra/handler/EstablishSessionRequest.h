#ifndef ESTABLISH_SESSION_REQUEST_H
#define ESTABLISH_SESSION_REQUEST_H

#include <string>
#include <iostream>

class EstablishSessionRequest {
    std::string username;

  public:
    EstablishSessionRequest(){};
    EstablishSessionRequest(std::string username) : username(username){};

    std::string getUsername() {
        return username;
    }

    friend std::ostream& operator<<(std::ostream& out,
                                    const EstablishSessionRequest& self) {
        return out << self.username.size() << ',' << self.username;
    }

    friend std::istream& operator>>(std::istream& in,
                                    EstablishSessionRequest& self) {
        std::string::size_type size;
        in >> size;
        in.ignore(1, ',');
        self.username.resize(size);
        in.read(&self.username[0], size);
        return in;
    }
};

#endif
