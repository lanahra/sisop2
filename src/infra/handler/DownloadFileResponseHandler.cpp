#include "infra/handler/DownloadFileResponseHandler.h"

#include <sstream>
#include <tuple>
#include "infra/handler/DownloadFileResponse.h"

void DownloadFileResponseHandler::handle(Message message,
                                         MessageStreamer& messageStreamer) {
    std::ignore = messageStreamer;
    DownloadFileResponse response = deserializeMessage(message.getBody());
    if (response.hasFile()) {
        service.saveLocal(response.getFile());
    } else {
        output << ERROR_MESSAGE;
        output.flush();
    }
}

DownloadFileResponse DownloadFileResponseHandler::deserializeMessage(
    std::string body) {
    std::stringstream serialized(body);
    DownloadFileResponse response;
    serialized >> response;
    return response;
}
