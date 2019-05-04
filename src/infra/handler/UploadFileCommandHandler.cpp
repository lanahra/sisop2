#include "infra/handler/UploadFileCommandHandler.h"

#include <sstream>
#include "infra/handler/UploadFileRequest.h"

void UploadFileCommandHandler::handle(std::vector<std::string> args,
                                      MessageStreamer &messageStreamer) {
    if (args.size() > 1) {
        Message command = commandFrom(args.at(1));
        messageStreamer.send(command);
    } else {
        output << ERROR_MESSAGE;
        output.flush();
    }
}

Message UploadFileCommandHandler::commandFrom(std::string filePath) {
    File file = userService.getLocal(filePath);
    UploadFileRequest request(username, file);
    std::stringstream serialized;
    serialized << request;
    return Message(operation, serialized.str());
}

