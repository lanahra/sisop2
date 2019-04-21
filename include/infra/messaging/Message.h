#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <iostream>

class Message {
    std::string operation;
    std::string body;
    std::string response;

  public:
    Message(){};
    Message(std::string operation, std::string body)
        : operation(operation), body(body), response(""){};
    Message(std::string operation, std::string body, std::string response)
        : operation(operation), body(body), response(response){};

    std::string getOperation() {
        return operation;
    }

    std::string getBody() {
        return body;
    }

    std::string getResponse() {
        return response;
    }

    friend bool operator==(const Message& self, const Message& other) {
        return self.operation == other.operation && self.body == other.body
            && self.response == other.response;
    }

    friend std::ostream& operator<<(std::ostream& out, const Message& self) {
        return out << self.operation.size() << ',' << self.operation << ','
                   << self.body.size() << ',' << self.body << ','
                   << self.response.size() << ',' << self.response;
    }

    friend std::istream& operator>>(std::istream& in, Message& self) {
        std::string::size_type size;
        in >> size;
        in.ignore(1, ',');
        self.operation.resize(size);
        in.read(&self.operation[0], size);
        in.ignore(1, ',');
        in >> size;
        in.ignore(1, ',');
        self.body.resize(size);
        in.read(&self.body[0], size);
        in.ignore(1, ',');
        in >> size;
        in.ignore(1, ',');
        self.response.resize(size);
        in.read(&self.response[0], size);
        return in;
    }
};

#endif
