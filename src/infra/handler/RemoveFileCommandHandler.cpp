#include "infra/handler/RemoveFileCommandHandler.h"
#include <sstream>
#include "infra/handler/RemoveFileRequest.h"

void RemoveFileCommandHandler::handle(std::vector<std::string> args,
                                      MessageStreamer& messageStreamer) {
    if (args.size() > 1) {
        Message command = commandFrom(args.at(1));
        messageStreamer.send(command);
    } else {
        output << ERROR_MESSAGE;
        output.flush();
    }
}

Message RemoveFileCommandHandler::commandFrom(std::string filename) {
    RemoveFileRequest request(username, filename);
    std::stringstream serialized;
    serialized << request;
    return Message(operation, serialized.str());
}
