#ifndef KEY_LOCK_H
#define KEY_LOCK_H

class KeyLock {
  public:
    virtual void lockRead(std::string key) = 0;
    virtual void unlockRead(std::string key) = 0;
    virtual void lockWrite(std::string key) = 0;
    virtual void unlockWrite(std::string key) = 0;
};

#endif