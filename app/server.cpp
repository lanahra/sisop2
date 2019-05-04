#include <map>
#include <memory>
#include <sstream>
#include "application/DefaultUserService.h"
#include "infra/handler/DownloadFileHandler.h"
#include "infra/handler/ListFileEntriesHandler.h"
#include "infra/handler/RemoveFileHandler.h"
#include "infra/handler/SaveFileHandler.h"
#include "infra/messaging/AsyncMessageListenerFactory.h"
#include "infra/messaging/ConnectionListener.h"
#include "infra/messaging/MessageHandler.h"
#include "infra/messaging/OpenListenerLoop.h"
#include "infra/messaging/TcpSocket.h"
#include "infra/repository/DefaultUserRepository.h"
#include "infra/repository/SystemFileRepository.h"

int main(int argc, char** argv) {
    int port;
    if (argc < 2) {
        std::cout << "port number expected" << std::endl;
        exit(EXIT_FAILURE);
    } else {
        std::stringstream arg;
        arg << argv[1];
        arg >> port;
    }

    SystemFileRepository fileRepository;
    DefaultUserRepository userRepository(fileRepository);
    DefaultUserService userService(userRepository, fileRepository);

    // create handler for command.establish_session
    auto listFileEntriesHandler
        = std::make_shared<ListFileEntriesHandler>(userService);

    auto downloadFileHandler
        = std::make_shared<DownloadFileHandler>(userService);

    auto removeFileHandler = std::make_shared<RemoveFileHandler>(userService);

    auto saveFileHandler = std::make_shared<SaveFileHandler>(userService);

    // register handlers
    std::map<std::string, std::shared_ptr<MessageHandler>> handlers;
    handlers["file.list.request"] = listFileEntriesHandler;
    handlers["file.download.request"] = downloadFileHandler;
    handlers["file.remove.request"] = removeFileHandler;
    handlers["file.upload.request"] = saveFileHandler;

    // factory for message listeners for every new connection
    OpenListenerLoop listenerLoop;
    AsyncMessageListenerFactory factory(listenerLoop, handlers);

    // starts listening for connections
    TcpSocket socket;
    ConnectionListener connectionListener(socket, listenerLoop, factory);
    connectionListener.listen(port);
}
