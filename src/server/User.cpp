#include "server/User.h"

User::User(std::string name) : name(name) {
    // empty constructor
}

void User::establishSession(Session session) {
    if (sessions.size() == MAX_ESTABLISHED_SESSIONS) {
        throw EstablishSessionException(name);
    }

    sessions.push_back(session);
}
