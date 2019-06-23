#include <sstream>
#include "infra/handler/UpdateBackupsListHandler.h"

void UpdateBackupsListHandler::handle(Message message, MessageStreamer& messageStreamer){
    UpdateBackupsListRequest request = deserializeMessage(message.getBody());
    replicaManagers.setBackupsDescriptions(request.getBackupsDescriptions());
    std::cout << "Updated backups list: " << message.getBody() << std::endl;
}

UpdateBackupsListRequest UpdateBackupsListHandler::deserializeMessage(
        std::string body) {
    std::stringstream serialized(body);
    UpdateBackupsListRequest request;
    serialized >> request;
    return request;
}