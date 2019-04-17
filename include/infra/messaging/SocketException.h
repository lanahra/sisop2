#ifndef SOCKET_EXCEPTION_H
#define SOCKET_EXCEPTION_H

class SocketException : public std::runtime_error {
  public:
    SocketException(std::string error)
        : std::runtime_error("SocketException: " + error){};
};

#endif
