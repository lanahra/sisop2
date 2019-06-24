#include "infra/handler/IpClientHandler.h"
#include <sstream>
#include <algorithm>

void IpClientHandler::handle(Message message, MessageStreamer& messageStreamer) {
    replicaManagers.broadcast(message);

    std::string ipclient = message.getBody();
    if(std::find(clientList.begin(), clientList.end(), ipclient) == clientList.end()){
      clientList.push_back(ipclient);
  }

    for(int i=0; i < clientList.size(); i++){
      std::cout << clientList.at(i) << ' ';
    }


}
