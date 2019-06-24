#ifndef SISOP2_SERVERDESCRIPTION_H
#define SISOP2_SERVERDESCRIPTION_H

#include <string>

struct ServerDescription {
    std::string address;
    int port;

    bool operator==(const ServerDescription& other) const {
        return address == other.address && port == other.port;
    }
};

#endif
