#include "infra/handler/ListServerDirectoriesHandler.h"
#include "infra/handler/ListServerDirectoriesResponse.h"
#include <sstream>

void ListServerDirectoriesHandler::handle(Message message, MessageStreamer &messageStreamer) {
    std::vector<std::string> usernames = fileRepository.getUsernamesFromSyncDirectories();
    ListServerDirectoriesResponse listServerDirectoriesResponse(usernames);
    std::stringstream serialized;
    serialized << listServerDirectoriesResponse;
    Message response(message.getResponse(), serialized.str());
    messageStreamer.send(response);
}