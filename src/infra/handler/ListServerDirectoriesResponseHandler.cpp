#include "infra/handler/ListServerDirectoriesResponseHandler.h"

#include <sstream>
#include <infra/handler/ListServerDirectoriesResponse.h>
#include <infra/handler/ListServerEntriesCommandHandler.h>
#include <string>

void ListServerDirectoriesResponseHandler::handle(Message message, MessageStreamer& messageStreamer) {
    ListServerDirectoriesResponse response = deserializeMessage(message.getBody());
    std::vector<std::string> usernames = response.getUsernames();
    for(std::string username : usernames){
        ListServerEntriesCommandHandler syncHandler = ListServerEntriesCommandHandler(
                        username, "file.list.request", "file.list.response");
        syncHandler.handle({}, messageStreamer);
    }
}

ListServerDirectoriesResponse ListServerDirectoriesResponseHandler::deserializeMessage(std::string body) {
    std::stringstream serialized(body);
    ListServerDirectoriesResponse response;
    serialized >> response;
    return response;
}