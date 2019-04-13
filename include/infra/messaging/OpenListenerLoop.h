#ifndef OPEN_LISTENER_LOOP_H
#define OPEN_LISTENER_LOOP_H

#include "ListenerLoop.h"

class OpenListenerLoop : public ListenerLoop {
  public:
    bool isOpen() {
        return true;
    }
};

#endif
