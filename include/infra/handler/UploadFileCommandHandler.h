//
// Created by christian on 28/04/19.
//

#ifndef SISOP2_UPLOADFILECOMMANDHANDLER_H
#define SISOP2_UPLOADFILECOMMANDHANDLER_H


#include <infra/messaging/CommandHandler.h>

class UploadFileCommandHandler : public CommandHandler {
    const std::string ERROR_MESSAGE = "upload command takes 1 argument\n";

    std::string username;
    std::string operation;
    std::string response;
    std::ostream& output;

    Message commandFrom(std::string filename);

public:
    UploadFileCommandHandler(std::string username,
                             std::string operation,
                             std::string response,
                             std::ostream& output)
             :  username(username),
                operation(operation),
                response(response),
                output(output){};
    void handle(std::vector<std::string> args,
                MessageStreamer& messageStreamer) override;
};


#endif
