#include <memory>
#include <iostream>
#include "infra/messaging/Socket.h"
#include "infra/messaging/TcpSocket.h"
#include "infra/messaging/SocketMessageStreamer.h"
#include "infra/messaging/Message.h"

int main() {
    auto socket = std::make_shared<TcpSocket>();
    socket->connect("127.0.0.1", 8888);

    SocketMessageStreamer messageStreamer(socket);

    Message message("file.list.request", "sixth");
    messageStreamer.send(message);

    Message receive = messageStreamer.receive();
    std::cout << receive.getOperation() << '\n' << receive.getBody() << '\n';
}
