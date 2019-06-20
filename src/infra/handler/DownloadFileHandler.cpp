#include "infra/handler/DownloadFileHandler.h"
#include <infra/repository/FileNotFoundException.h>
#include <sstream>

void DownloadFileHandler::handle(Message message,
                                 MessageStreamer& messageStreamer) {
    DownloadFileRequest request = deserializeRequest(message.getBody());
    DownloadFileResponse response = handle(request);
    messageStreamer.send(
        Message(message.getResponse(), serializeResponse(response)));
}

DownloadFileRequest DownloadFileHandler::deserializeRequest(std::string body) {
    std::stringstream serialized(body);
    DownloadFileRequest request;
    serialized >> request;
    return request;
}

DownloadFileResponse DownloadFileHandler::handle(DownloadFileRequest request) {
    try {
        File file = tryToGetFile(request);
        return DownloadFileResponse(request.getUsername(), file);
    } catch (const FileNotFoundException& e) {
        return DownloadFileResponse(request.getUsername());
    }
}
File DownloadFileHandler::tryToGetFile(DownloadFileRequest request) {
    return service.getFile(request.getUsername(), request.getFilename());
}

std::string DownloadFileHandler::serializeResponse(
    DownloadFileResponse response) {
    std::stringstream serialized;
    serialized << response;
    return serialized.str();
}
