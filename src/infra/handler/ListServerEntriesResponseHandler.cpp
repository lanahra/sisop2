#include "infra/handler/ListServerEntriesResponseHandler.h"

#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "infra/handler/ListFileEntriesResponse.h"

void ListServerEntriesResponseHandler::handle(
    Message message,
    MessageStreamer& messageStreamer) {
    std::ignore = messageStreamer;
    ListFileEntriesResponse response = deserializeMessage(message.getBody());
    service.printEntries(response.getEntries());
}

ListFileEntriesResponse ListServerEntriesResponseHandler::deserializeMessage(
    std::string body) {
    std::stringstream serialized(body);
    ListFileEntriesResponse response;
    serialized >> response;
    return response;
}