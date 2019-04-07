#ifndef SESSION_H
#define SESSION_H

class Session {
    friend bool operator==(const Session& self, const Session& other) {
        return true;
    }
};

#endif
