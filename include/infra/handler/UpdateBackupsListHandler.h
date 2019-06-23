#ifndef SISOP2_UPDATEBACKUPSLISTHANDLER_H
#define SISOP2_UPDATEBACKUPSLISTHANDLER_H


#include <infra/messaging/MessageHandler.h>
#include <server/ReplicaManagers.h>

class UpdateBackupsListHandler : public MessageHandler{
    ReplicaManagers& replicaManagers;

  public:
    UpdateBackupsListHandler(ReplicaManagers& replicaManagers) : replicaManagers(replicaManagers){};
    void handle(Message message, MessageStreamer& messageStreamer) override;
    UpdateBackupsListRequest deserializeMessage(std::string body);
};


#endif
