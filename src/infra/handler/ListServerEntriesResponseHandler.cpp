#include "infra/handler/ListServerEntriesResponseHandler.h"

#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "infra/handler/ListFileEntriesResponse.h"

void ListServerEntriesResponseHandler::handle(
    Message message,
    MessageStreamer& messageStreamer) {
    ListFileEntriesResponse response = deserializeMessage(message.getBody());
    printHeader();
    printEntries(response.getEntries());
    output.flush();
}

ListFileEntriesResponse ListServerEntriesResponseHandler::deserializeMessage(
    std::string body) {
    std::stringstream serialized(body);
    ListFileEntriesResponse response;
    serialized >> response;
    return response;
}

void ListServerEntriesResponseHandler::printHeader() {
    output << std::left << std::setw(24) << "last modified" << std::setw(24)
           << "last accessed" << std::setw(24) << "last changed"
           << "file" << std::endl;
}

void ListServerEntriesResponseHandler::printEntries(
    std::list<FileEntry> entries) {
    for (FileEntry entry : entries) {
        output << std::setw(24)
               << formatTimestamp(entry.getTimestamps().getLastModification())
               << std::setw(24)
               << formatTimestamp(entry.getTimestamps().getLastAccess())
               << std::setw(24)
               << formatTimestamp(entry.getTimestamps().getLastChange())
               << entry.getName() << std::endl;
    }
}

std::string ListServerEntriesResponseHandler::formatTimestamp(
    std::time_t time) {
    std::stringstream format;
    format << std::put_time(localtime(&time), "%Y-%m-%d %X");
    return format.str();
}
