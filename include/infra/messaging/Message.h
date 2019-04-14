#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <iostream>

class Message {
    std::string operation;
    std::string body;

  public:
    Message(){};
    Message(std::string operation, std::string body)
        : operation(operation), body(body){};

    std::string getOperation() {
        return operation;
    }

    std::string getBody() {
        return body;
    }

    friend std::ostream& operator<<(std::ostream& out, const Message& self) {
        out << self.operation.size() << ',' << self.operation << ','
            << self.body.size() << ',' << self.body;
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
    }
};

#endif
