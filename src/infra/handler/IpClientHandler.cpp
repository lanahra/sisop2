#include "infra/handler/IpClientHandler.h"
#include <sstream>

void IpClientHandler::handle(Message message,
                                    MessageStreamer& messageStreamer) {
    std::string ipclient = message.getBody();
    std::cout << ipclient << std::endl;
}
