#include "infra/handler/ListServerDirectoriesResponseHandler.h"

#include <sstream>
#include <infra/handler/ListServerDirectoriesResponse.h>

void ListServerDirectoriesResponseHandler::handle(Message message, MessageStreamer& messageStreamer) {
    ListServerDirectoriesResponse response = deserializeMessage(message.getBody());
    std::vector<std::string> usernames = response.getUsernames();
    for(std::string username : usernames){
        // userService.syncUser()
    }

}

ListServerDirectoriesResponse ListServerDirectoriesResponseHandler::deserializeMessage(std::string body) {
    std::stringstream serialized(body);
    ListServerDirectoriesResponse response;
    serialized >> response;
    return response;
}