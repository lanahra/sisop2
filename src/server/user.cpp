#include <server/user.h>

User::User(std::string name, std::list<File> files) : name(name), files(files) {
    // empty constructor
}

void User::establishSession(Session session) {
    if (sessions.size() == MAX_ESTABLISHED_SESSIONS) {
        throw EstablishSessionException(name);
    }

    sessions.push_back(session);
}
