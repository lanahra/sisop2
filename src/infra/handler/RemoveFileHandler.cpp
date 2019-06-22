#include "infra/handler/RemoveFileHandler.h"
#include <sstream>
#include <tuple>
#include "infra/handler/RemoveFileRequest.h"

void RemoveFileHandler::handle(Message message, MessageStreamer& socket) {
    replicaManagers.broadcast(message);

    std::ignore = socket;
    std::stringstream serialized(message.getBody());
    RemoveFileRequest request;
    serialized >> request;
    handle(request);
}

void RemoveFileHandler::handle(RemoveFileRequest request) {
    service.removeFile(request.getUsername(), request.getFilename());
}
