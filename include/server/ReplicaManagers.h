#ifndef SISOP2_REPLICAMANAGERS_H
#define SISOP2_REPLICAMANAGERS_H


#include <infra/messaging/Socket.h>
#include <list>
#include <infra/messaging/Message.h>

class ReplicaManagers {
    std::list<std::shared_ptr<Socket>> sockets;

  public:
    ReplicaManagers(): sockets(){};

    void addSocket(std::shared_ptr<Socket> socket){sockets.push_back(socket);};
    std::list<std::shared_ptr<Socket>> getSockets(){return sockets;};
    void broadcast(Message message);
};

#endif