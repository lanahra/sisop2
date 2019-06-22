#include "infra/messaging/SocketMessageStreamer.h"

#include <sstream>

Message SocketMessageStreamer::receive() {
    std::unique_lock<std::mutex> lk(readMutex);
    int length = socket->readInt();
    std::string serialized = socket->read(length);
    return messageFrom(serialized);
}

Message SocketMessageStreamer::messageFrom(std::string serialized) {
    std::stringstream s(serialized);
    Message message;
    s >> message;
    return message;
}

void SocketMessageStreamer::send(Message message) {
    std::unique_lock<std::mutex> lk(writeMutex);
    std::string serialized = serializedFrom(message);
    socket->writeInt(serialized.size());
    socket->write(serialized);
}

std::string SocketMessageStreamer::serializedFrom(Message message) {
    std::stringstream serialized;
    serialized << message;
    return serialized.str();
}

void SocketMessageStreamer::close() {
    socket->close();
}

std::shared_ptr<Socket> SocketMessageStreamer::getSocket() {
    return socket;
}