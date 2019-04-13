#ifndef LISTENER_LOOP_H
#define LISTENER_LOOP_H

class ListenerLoop {
  public:
    virtual ~ListenerLoop() = default;
    virtual bool isOpen() = 0;
};

#endif
