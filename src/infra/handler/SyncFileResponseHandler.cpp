#include "infra/handler/SyncFileResponseHandler.h"

#include <sstream>
#include <tuple>
#include "infra/handler/DownloadFileResponse.h"

void SyncFileResponseHandler::handle(Message message,
                                         MessageStreamer& messageStreamer) {
    std::ignore = messageStreamer;
    DownloadFileResponse response = deserializeMessage(message.getBody());
    if (response.hasFile()) {
        service.saveFile(username, response.getFile());
    }
}

DownloadFileResponse SyncFileResponseHandler::deserializeMessage(
    std::string body) {
    std::stringstream serialized(body);
    DownloadFileResponse response;
    serialized >> response;
    return response;
}
