#ifndef SISOP2_LISTSERVERDIRECTORIESRESPONSE_H
#define SISOP2_LISTSERVERDIRECTORIESRESPONSE_H


#include <vector>
#include <string>
#include <ostream>
#include <iostream>

class ListServerDirectoriesResponse {
    std::vector<std::string> usernames;

public:
    ListServerDirectoriesResponse(){};
    ListServerDirectoriesResponse(std::vector<std::string> usernames)
            : usernames(usernames){};

    std::vector<std::string> getUsernames() {
        return usernames;
    }

    friend bool operator==(const ListServerDirectoriesResponse& self,
                           const ListServerDirectoriesResponse& other) {
        return self.usernames.size() == other.usernames.size();
    }

    friend std::ostream& operator<<(std::ostream& out,
                                    const ListServerDirectoriesResponse& self) {
        out << self.usernames.size();
        for (std::string username : self.usernames) {
            out << ',' << username;
        }
        return out;
    }

    friend std::istream& operator>>(std::istream& in, ListServerDirectoriesResponse& self) {
        size_t size;
        in >> size;
        for (size_t i = 0; i < size; i++) {
            in.ignore(1, ',');
            std::string username;
            in >> username;
            self.usernames.push_back(username);
        }
        return in;
    }
};

#endif
