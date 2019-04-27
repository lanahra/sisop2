#include "infra/handler/DownloadFileCommandHandler.h"

#include <sstream>
#include "infra/handler/DownloadFileRequest.h"

void DownloadFileCommandHandler::handle(std::vector<std::string> args,
                                        MessageStreamer& messageStreamer) {
    if (args.size() > 1) {
        Message command = commandFrom(args.at(1));
        messageStreamer.send(command);
    } else {
        output << ERROR_MESSAGE;
        output.flush();
    }
}

Message DownloadFileCommandHandler::commandFrom(std::string filename) {
    DownloadFileRequest request(username, filename);
    std::stringstream serialized;
    serialized << request;
    return Message(operation, serialized.str(), response);
}
