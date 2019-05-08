#ifndef READ_WRITE_LOCK_H
#define READ_WRITE_LOCK_H

#include <condition_variable>
#include <mutex>

class ReadWriteLock {
    int readers;
    bool writer;
    std::mutex mutex;
    std::condition_variable cv;

  public:
    ReadWriteLock() : readers(0), writer(false){};
    void lockRead();
    void unlockRead();
    void lockWrite();
    void unlockWrite();
    bool isIdle();
};

#endif