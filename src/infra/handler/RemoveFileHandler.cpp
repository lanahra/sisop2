#include "infra/handler/RemoveFileHandler.h"
#include "infra/handler/RemoveFileRequest.h"
#include <sstream>

void RemoveFileHandler::handle(Message message, MessageStreamer& socket) {
    std::stringstream serialized(message.getBody());
    RemoveFileRequest request;
    serialized >> request;
    handle(request);
}

void RemoveFileHandler::handle(RemoveFileRequest request) {
    service.removeFile(request.getUsername(), request.getFilename());
}
