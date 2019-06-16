#ifndef SISOP2_LISTSERVERDIRECTORIESRESPONSEHANDLER_H
#define SISOP2_LISTSERVERDIRECTORIESRESPONSEHANDLER_H


#include <infra/messaging/MessageHandler.h>
#include <application/UserService.h>
#include "ListServerDirectoriesResponse.h"

class ListServerDirectoriesResponseHandler : MessageHandler{
    UserService& userService;

  public:
    ListServerDirectoriesResponseHandler(UserService& service) : userService(userService){};
    void handle(Message message, MessageStreamer& messageStreamer) override;

    ListServerDirectoriesResponse deserializeMessage(std::string body);
};


#endif
