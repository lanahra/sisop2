#include "infra/handler/EstablishSessionHandler.h"

#include <sstream>
#include <iostream>

void EstablishSessionHandler::handle(std::string message, Socket& socket) {
    std::stringstream serialized(message);
    EstablishSessionRequest request;
    serialized >> request;
    handle(request, socket);
}

void EstablishSessionHandler::handle(EstablishSessionRequest request,
                                     Socket& socket) {
    std::cout << request.getUsername();
    std::cout.flush();
}
