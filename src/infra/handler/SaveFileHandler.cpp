#include "infra/handler/SaveFileHandler.h"

#include <sstream>
#include <infra/handler/UploadFileRequest.h>
#include <tuple>

void SaveFileHandler::handle(Message message, MessageStreamer& socket) {
    replicaManagers.broadcast(message);

    std::ignore = socket;
    std::stringstream serialized(message.getBody());
    UploadFileRequest request;
    serialized >> request;
    handle(request);
}

void SaveFileHandler::handle(UploadFileRequest request) {
    service.saveFile(request.getUsername(), request.getFile());
}