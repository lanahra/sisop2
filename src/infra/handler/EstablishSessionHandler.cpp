#include "infra/handler/EstablishSessionHandler.h"

#include <sstream>
#include <iostream>

void EstablishSessionHandler::handle(std::string message,
                                     MessageStreamer& messageStreamer) {
    std::stringstream serialized(message);
    EstablishSessionRequest request;
    serialized >> request;
    handle(request, messageStreamer);
}

void EstablishSessionHandler::handle(EstablishSessionRequest request,
                                     MessageStreamer& messageStreamer) {
    std::cout << request.getUsername() << '\n';
    std::cout.flush();
}
