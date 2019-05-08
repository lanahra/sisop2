#include "infra/synchronization/DefaultKeyLock.h"

void DefaultKeyLock::lockRead(std::string key) {
    std::unique_lock<std::mutex> lk(mutex);
    auto lock = lockFor(key);
    lock->lockRead();
}

void DefaultKeyLock::unlockRead(std::string key) {
    std::unique_lock<std::mutex> lk(mutex);
    auto lock = lockFor(key);
    lock->unlockRead();
    if (lock->isIdle()) {
        clearLock(key);
    }
}

void DefaultKeyLock::lockWrite(std::string key) {
    std::unique_lock<std::mutex> lk(mutex);
    auto lock = lockFor(key);
    lock->lockWrite();
}

void DefaultKeyLock::unlockWrite(std::string key) {
    std::unique_lock<std::mutex> lk(mutex);
    auto lock = lockFor(key);
    lock->unlockWrite();
    if (lock->isIdle()) {
        clearLock(key);
    }
}

std::shared_ptr<ReadWriteLock> DefaultKeyLock::lockFor(std::string key) {
    try {
        return locks.at(key);
    } catch (const std::out_of_range& e) {
        auto lock = std::make_shared<ReadWriteLock>();
        locks[key] = lock;
        return lock;
    }
}

void DefaultKeyLock::clearLock(std::string key) {
    locks.erase(key);
}
