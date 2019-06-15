#include <map>
#include <memory>
#include <sstream>
#include <infra/messaging/SocketMessageStreamer.h>
#include <infra/messaging/BlockingMessageListener.h>
#include <infra/messaging/AsyncMessageListener.h>
#include <infra/handler/ListServerDirectoriesHandler.h>
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
#include "infra/synchronization/DefaultKeyLock.h"

struct ServerDescription {
    std::string address;
    int port;
};

void runPrimaryServer(int port);

void runBackupServer(struct ServerDescription primaryServer){
    std::cout << "This is a backup server whose primary server is at "
                << primaryServer.address << ":"
                << primaryServer.port << std::endl;

    OpenListenerLoop listenerLoop;
    auto socket = std::make_shared<TcpSocket>();
    socket->connect(primaryServer.address, primaryServer.port);

    auto messageStreamer = std::make_shared<SocketMessageStreamer>(socket);

    // register handlers
    std::map<std::string, std::shared_ptr<MessageHandler>> messageHandlers;

    auto messageListener
            = std::unique_ptr<BlockingMessageListener>(new BlockingMessageListener(
                    messageStreamer, listenerLoop, messageHandlers));
    AsyncMessageListener asyncMessageListener(std::move(messageListener));
    asyncMessageListener.listen();

    // first sync between backup and primary
    Message message("server.list.request", "", "server.list.response");
    messageStreamer->send(message);
}

void runPrimaryServer(int port) {
    SystemFileRepository fileRepository;
    DefaultUserRepository userRepository(fileRepository);
    DefaultKeyLock keyLock;
    DefaultUserService userService(userRepository, fileRepository, keyLock);

    // create handler for command.establish_session
    auto listFileEntriesHandler
            = std::make_shared<ListFileEntriesHandler>(userService);

    auto downloadFileHandler
            = std::make_shared<DownloadFileHandler>(userService);

    auto removeFileHandler = std::make_shared<RemoveFileHandler>(userService);

    auto saveFileHandler = std::make_shared<SaveFileHandler>(userService);

    auto listServerDirsHandler = std::make_shared<ListServerDirectoriesHandler>(fileRepository);

    // register handlers
    std::map<std::string, std::shared_ptr<MessageHandler>> handlers;
    handlers["file.list.request"] = listFileEntriesHandler;
    handlers["file.download.request"] = downloadFileHandler;
    handlers["file.remove.request"] = removeFileHandler;
    handlers["file.upload.request"] = saveFileHandler;
    handlers["server.list.request"] = listServerDirsHandler;

    // factory for message listeners for every new connection
    OpenListenerLoop listenerLoop;
    AsyncMessageListenerFactory factory(listenerLoop, handlers);

    // starts listening for connections
    TcpSocket socket;
    ConnectionListener connectionListener(socket, listenerLoop, factory);
    connectionListener.listen(port);
}

int main(int argc, char** argv) {
    int port;
    struct ServerDescription primaryServer;
    if (argc < 2) {
        std::cout << "port number expected" << std::endl;
        exit(EXIT_FAILURE);
    } else {
        std::stringstream arg;
        arg << argv[1];
        arg >> port;
        if (argc == 4) { //Indica servidor backup (que passou o primario como entrada)
            std::stringstream arg;
            arg << argv[2];
            primaryServer.address = arg.str();
            arg.str("");
            arg << argv[3];
            arg >> primaryServer.port;
            runBackupServer(primaryServer);
        }else{
            runPrimaryServer(port);
        }
    }
}


