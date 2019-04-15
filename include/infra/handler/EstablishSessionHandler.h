#ifndef ESTABLISH_SESSION_HANDLER_H
#define ESTABLISH_SESSION_HANDLER_H

#include "infra/messaging/MessageHandler.h"
#include "infra/messaging/Socket.h"
#include "infra/handler/EstablishSessionRequest.h"

class EstablishSessionHandler : public MessageHandler {
    void handle(EstablishSessionRequest request, Socket& socket);

  public:
    EstablishSessionHandler(){};
    void handle(std::string message, Socket& socket) override;
};

#endif
