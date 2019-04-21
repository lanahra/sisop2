#include <iostream>
#include <memory>
#include "infra/messaging/Message.h"
#include "infra/messaging/Socket.h"
#include "infra/messaging/SocketMessageStreamer.h"
#include "infra/messaging/TcpSocket.h"

int main() {
    auto socket = std::make_shared<TcpSocket>();
    socket->connect("127.0.0.1", 8888);

    SocketMessageStreamer messageStreamer(socket);

    Message message("file.list.request", "sixth", "file.list.response");
    messageStreamer.send(message);

    Message receive = messageStreamer.receive();
    std::cout << receive.getOperation() << '\n' << receive.getBody() << '\n';

    Message downloadRequest(
        "file.download.request", "5,sixth,5,first", "file.download.response");
    messageStreamer.send(downloadRequest);

    Message downloadResponse = messageStreamer.receive();
    std::cout << downloadResponse.getOperation() << '\n'
              << downloadResponse.getBody() << '\n';
}
