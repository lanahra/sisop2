#ifndef SISOP2_LISTSERVERDIRECTORIESHANDLER_H
#define SISOP2_LISTSERVERDIRECTORIESHANDLER_H


#include "infra/messaging/MessageHandler.h"
#include "server/FileRepository.h"

class ListServerDirectoriesHandler : public MessageHandler {
    FileRepository& fileRepository;

  public:
    ListServerDirectoriesHandler(FileRepository& fileRepository)
    : fileRepository(fileRepository){};
    void handle(Message message, MessageStreamer& messageStreamer) override;
};


#endif
