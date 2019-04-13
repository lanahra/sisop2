#include <gmock/gmock.h>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "infra/messaging/TcpSocket.h"

TEST(TcpSocketTest, AcceptsNewConnection) {
    std::mutex m;
    std::condition_variable cv;
    std::shared_ptr<Socket> socket_;
    bool ready;
    std::thread t([&] {
        TcpSocket server;
        server.listen(8888);

        {
            std::unique_lock<std::mutex> lk(m);
            ready = true;
        }
        cv.notify_one();

        socket_ = server.accept();
    });

    {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, [&] { return ready; });
    }

    TcpSocket client;
    client.connect("127.0.0.1", 8888);

    t.join();
}
