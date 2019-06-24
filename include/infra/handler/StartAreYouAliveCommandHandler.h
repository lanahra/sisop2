#ifndef SISOP2_STARTAREYOUALIVECOMMANDHANDLER_H
#define SISOP2_STARTAREYOUALIVECOMMANDHANDLER_H


#include <infra/messaging/CommandHandler.h>

class StartAreYouAliveCommandHandler : public CommandHandler{
    std::string operation;
  public:
    StartAreYouAliveCommandHandler(std::string operation)
    : operation(operation){};
    void handle(std::vector<std::string> args,
                MessageStreamer& messageStreamer) override;

};


#endif
