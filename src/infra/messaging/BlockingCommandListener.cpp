#include "infra/messaging/BlockingCommandListener.h"
#include <iterator>
#include <sstream>

void BlockingCommandListener::listen() {
    try {
        tryToListen();
    } catch (const std::exception& e) {
        std::clog << e.what() << std::endl;
        std::clog.flush();
    }
}

void BlockingCommandListener::tryToListen() {
    std::string line;
    while (listenerLoop.isOpen()) {
        std::getline(input, line);
        std::vector<std::string> args = argsFrom(line);

        if (handlerExistsFor(args)) {
            CommandHandler& handler = handlerFor(args);
            handler.handle(args, *messageStreamer);
        } else {
            continue;
        }
    }
}

std::vector<std::string> BlockingCommandListener::argsFrom(std::string line) {
    std::istringstream iss(line);
    return std::vector<std::string>(std::istream_iterator<std::string>{iss},
                                    std::istream_iterator<std::string>());
}

bool BlockingCommandListener::handlerExistsFor(std::vector<std::string> args) {
    return args.size() > 0 && handlers.find(args.at(0)) != handlers.end();
}

CommandHandler& BlockingCommandListener::handlerFor(
    std::vector<std::string> args) {
    return *handlers.at(args.at(0));
}
