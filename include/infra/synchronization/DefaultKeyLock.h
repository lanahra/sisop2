#ifndef DEFAULT_KEY_LOCK_H
#define DEFAULT_KEY_LOCK_H

#include <map>
#include <mutex>
#include <string>
#include "ReadWriteLock.h"
#include "application/KeyLock.h"

class DefaultKeyLock : public KeyLock {
    std::mutex mutex;
    std::map<std::string, std::shared_ptr<ReadWriteLock>> locks;

  public:
    void lockRead(std::string key) override;
    void unlockRead(std::string key) override;
    void lockWrite(std::string key) override;
    void unlockWrite(std::string key) override;
    std::shared_ptr<ReadWriteLock> lockFor(std::string key);
    void clearLock(std::string key);
};

#endif