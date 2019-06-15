#ifndef SISOP2_LISTSERVERDIRECTORIESHANDLER_H
#define SISOP2_LISTSERVERDIRECTORIESHANDLER_H


#include <infra/messaging/MessageHandler.h>
#include <infra/repository/SystemFileRepository.h>

class ListServerDirectoriesHandler : public MessageHandler {
    SystemFileRepository& systemFileRepository;

  public:
    ListServerDirectoriesHandler(SystemFileRepository& systemFileRepository)
    : systemFileRepository(systemFileRepository){};
    void handle(Message message, MessageStreamer& messageStreamer) override;
};


#endif
