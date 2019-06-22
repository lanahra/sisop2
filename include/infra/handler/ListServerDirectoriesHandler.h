#ifndef SISOP2_LISTSERVERDIRECTORIESHANDLER_H
#define SISOP2_LISTSERVERDIRECTORIESHANDLER_H


#include <server/ReplicaManagers.h>
#include "infra/messaging/MessageHandler.h"
#include "server/FileRepository.h"

class ListServerDirectoriesHandler : public MessageHandler {
    FileRepository& fileRepository;
    ReplicaManagers& replicaManagers;

  public:
    ListServerDirectoriesHandler(FileRepository& fileRepository, ReplicaManagers& replicaManagers)
    : fileRepository(fileRepository), replicaManagers(replicaManagers){};
    void handle(Message message, MessageStreamer& messageStreamer) override;
};


#endif
