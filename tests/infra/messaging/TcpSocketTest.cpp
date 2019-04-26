#include <gmock/gmock.h>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "infra/messaging/TcpSocket.h"
#include "infra/messaging/SocketException.h"

using ::testing::Eq;

TEST(TcpSocketTest, AcceptsNewConnection) {
    std::mutex m;
    std::condition_variable cv;
    std::shared_ptr<Socket> socket_;
    bool ready;
    std::thread t([&] {
        TcpSocket server;
        server.listen(8888);

        std::unique_lock<std::mutex> lk(m);
        ready = true;
        cv.notify_one();
        lk.unlock();

        socket_ = server.accept();
    });

    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk, [&] { return ready; });
    lk.unlock();

    TcpSocket client;
    client.connect("127.0.0.1", 8888);

    t.join();
}

TEST(TcpSocketTest, WritesAndReadsInt) {
    std::mutex m;
    std::condition_variable cv;
    std::shared_ptr<Socket> socket_;
    bool ready;
    std::thread t([&] {
        TcpSocket server;
        server.listen(8889);

        std::unique_lock<std::mutex> lk(m);
        ready = true;
        cv.notify_one();
        lk.unlock();

        socket_ = server.accept();
        EXPECT_THAT(socket_->readInt(), Eq(2));
    });

    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk, [&] { return ready; });
    lk.unlock();

    TcpSocket client;
    client.connect("127.0.0.1", 8889);
    client.writeInt(2);

    t.join();
}

TEST(TcpSocketTest, WritesAndReadsString) {
    std::mutex m;
    std::condition_variable cv;
    std::shared_ptr<Socket> socket_;
    bool ready;
    std::thread t([&] {
        TcpSocket server;
        server.listen(8890);

        std::unique_lock<std::mutex> lk(m);
        ready = true;
        cv.notify_one();
        lk.unlock();

        socket_ = server.accept();
        EXPECT_THAT(socket_->read(8), Eq("a string"));
    });

    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk, [&] { return ready; });
    lk.unlock();

    TcpSocket client;
    client.connect("127.0.0.1", 8890);
    client.write("a string");

    t.join();
}

TEST(TcpSocketTest, ThrowsExceptionOnConnectError) {
    TcpSocket client;
    EXPECT_THROW(client.connect("invalid host", 1234), SocketException);
}
