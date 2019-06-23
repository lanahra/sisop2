
#include <list>
#include <stdexcept>
#include "infra/messaging/MessageHandler.h"

class IpClientHandler : public MessageHandler {
    //std::list<std::string>& clientList;



  public:
    IpClientHandler(){};
    void handle(Message message, MessageStreamer& messageStreamer) override;

};
