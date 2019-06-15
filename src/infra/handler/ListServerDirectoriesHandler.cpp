#include <infra/handler/ListServerDirectoriesResponse.h>
#include <sstream>
#include "infra/handler/ListServerDirectoriesHandler.h"

void ListServerDirectoriesHandler::handle(Message message, MessageStreamer &messageStreamer) {
    std::vector<std::string> usernames = systemFileRepository.getUsernamesFromSyncDirectories();
    ListServerDirectoriesResponse listServerDirectoriesResponse(usernames);
    std::stringstream serialized;
    serialized << listServerDirectoriesResponse;
    Message response(message.getResponse(), serialized.str());
    messageStreamer.send(response);
}