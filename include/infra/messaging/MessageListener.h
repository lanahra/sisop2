#ifndef MESSAGE_LISTENER_H
#define MESSAGE_LISTENER_H

class MessageListener {
  public:
    virtual ~MessageListener() = default;
    virtual void listen() = 0;
};

#endif
