#ifndef UPLOAD_FILE_COMMAND_HANDLER_H
#define UPLOAD_FILE_COMMAND_HANDLER_H


#include <infra/messaging/CommandHandler.h>
#include <application/DefaultUserService.h>

class UploadFileCommandHandler : public CommandHandler {
    const std::string ERROR_ARGS = "upload command takes 1 argument\n";
    const std::string ERROR_NOT_FOUND = "file not found\n";

    std::string username;
    std::string operation;
    UserService& userService;
    std::ostream& output;

    Message commandFrom(std::string filename);
    void tryToHandle(std::vector<std::string> args, MessageStreamer& messageStreamer);

  public:
    UploadFileCommandHandler(std::string username,
                             std::string operation,
                             UserService& userService,
                             std::ostream& output)
             :  username(username),
                operation(operation),
                userService(userService),
                output(output){};
    void handle(std::vector<std::string> args,
                MessageStreamer& messageStreamer) override;
};


#endif
