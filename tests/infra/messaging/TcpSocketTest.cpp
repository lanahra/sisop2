#include <gmock/gmock.h>
#include <memory>
#include <thread>
#include "infra/messaging/TcpSocket.h"

TEST(TcpSocketTest, AcceptsNewConnection) {
    std::shared_ptr<Socket> socket_;
    std::thread t([&] {
        TcpSocket server;
        server.listen(8888);
        socket_ = server.accept();
    });

    TcpSocket client;
    client.connect("127.0.0.1", 8888);

    t.join();
}
