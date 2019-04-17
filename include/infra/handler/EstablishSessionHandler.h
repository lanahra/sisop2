#ifndef ESTABLISH_SESSION_HANDLER_H
#define ESTABLISH_SESSION_HANDLER_H

#include "infra/messaging/MessageHandler.h"
#include "infra/messaging/MessageStreamer.h"
#include "infra/handler/EstablishSessionRequest.h"

class EstablishSessionHandler : public MessageHandler {
    void handle(EstablishSessionRequest request, MessageStreamer& socket);

  public:
    EstablishSessionHandler(){};
    void handle(std::string message, MessageStreamer& socket) override;
};

#endif
