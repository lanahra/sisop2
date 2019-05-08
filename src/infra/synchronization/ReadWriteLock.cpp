#include "infra/synchronization/ReadWriteLock.h"

void ReadWriteLock::lockRead() {
    std::unique_lock<std::mutex> lk(mutex);
    cv.wait(lk, [&] { return !writer;});
    readers++;
}

void ReadWriteLock::unlockRead() {
    std::unique_lock<std::mutex> lk(mutex);
    readers--;
    if (readers == 0) {
        cv.notify_all();
    }
}

void ReadWriteLock::lockWrite() {
    std::unique_lock<std::mutex> lk(mutex);
    cv.wait(lk, [&] { return !writer && readers == 0;});
    writer = true;
}

void ReadWriteLock::unlockWrite() {
    std::unique_lock<std::mutex> lk(mutex);
    writer = false;
    cv.notify_all();
}

bool ReadWriteLock::isIdle() {
    return !writer && readers == 0;
}
