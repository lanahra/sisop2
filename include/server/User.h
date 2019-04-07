#ifndef USER_H
#define USER_H

#include <string>
#include <list>
#include <stdexcept>
#include "File.h"
#include "Session.h"

class User {
    const unsigned int MAX_ESTABLISHED_SESSIONS = 2;

    std::string name;
    std::list<File> files;
    std::list<Session> sessions;

  public:
    User(std::string name);
    User(std::string name, std::list<File> files);
    void establishSession(Session session);

    std::list<File> getFiles() {
        return files;
    }

    std::list<Session> getSessions() {
        return sessions;
    }
};

class EstablishSessionException : public std::runtime_error {
  public:
    EstablishSessionException(std::string name)
        : std::runtime_error("Cannot establish new session for user: " + name) {
    }
};

#endif
