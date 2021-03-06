#include "infra/handler/ListServerDirectoriesHandler.h"
#include "infra/handler/ListServerDirectoriesResponse.h"
#include <sstream>
#include <infra/handler/ListServerDirectoriesRequest.h>

void ListServerDirectoriesHandler::handle(Message message, MessageStreamer &messageStreamer) {
    ListServerDirectoriesRequest request = deserializeMessage(message.getBody());
    std::cout << "Chegou primeiro request de " << request.getAddress() << ":" << request.getPort() << std::endl;
    replicaManagers.addSocket(messageStreamer.getSocket());
    replicaManagers.addBackupServerDescription(request.getAddress(), request.getPort());
    replicaManagers.broadcastNewBackupsList();

    std::vector<std::string> usernames = fileRepository.getUsernamesFromSyncDirectories();
    ListServerDirectoriesResponse listServerDirectoriesResponse(usernames);
    std::stringstream serialized;
    serialized << listServerDirectoriesResponse;
    Message response(message.getResponse(), serialized.str());
    messageStreamer.send(response);
}

ListServerDirectoriesRequest ListServerDirectoriesHandler::deserializeMessage(
        std::string body) {
    std::stringstream serialized(body);
    ListServerDirectoriesRequest request;
    serialized >> request;
    return request;
}