#include <map>
#include <memory>
#include <sstream>
#include <infra/handler/ListServerDirectoriesResponse.h>
#include <infra/handler/ListServerDirectoriesResponseHandler.h>
#include <infra/handler/DownloadFileResponseHandler.h>
#include <infra/handler/SyncFileResponseHandler.h>
#include <infra/handler/SyncEndpoints.h>
#include <infra/handler/SyncEntriesResponseHandler.h>
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
#include "infra/messaging/SocketMessageStreamer.h"
#include "infra/messaging/BlockingMessageListener.h"
#include "infra/messaging/AsyncMessageListener.h"
#include "infra/handler/ListServerDirectoriesHandler.h"

struct ServerDescription {
    std::string address;
    int port;
};

void runPrimaryServer(int port);

void runBackupServer(struct ServerDescription primaryServer){
    std::cout << "This is a backup server whose primary server is at "
                << primaryServer.address << ":"
                << primaryServer.port << std::endl;

    SystemFileRepository fileRepository;
    DefaultUserRepository userRepository(fileRepository);
    DefaultKeyLock keyLock;
    DefaultUserService userService(userRepository, fileRepository, keyLock);
    OpenListenerLoop listenerLoop;

    auto socket = std::make_shared<TcpSocket>();
    socket->connect(primaryServer.address, primaryServer.port);

    auto messageStreamer = std::make_shared<SocketMessageStreamer>(socket);

    auto listServerDirsResponseHandler = std::make_shared<ListServerDirectoriesResponseHandler>();

    auto downloadFileResponseHandler
            = std::make_shared<DownloadFileResponseHandler>(userService, std::cout);
    auto syncFileResponseHandler = std::make_shared<SyncFileResponseHandler>(userService);

    SyncEndpoints endpoints
            = SyncEndpoints::Builder()
                    .withDownloadFile("file.download.request", "file.sync.response")
                    .withRemoveFile("file.remove.request")
                    .withUploadFile("file.upload.request")
                    .build();
    auto syncEntriesResponseHandler
            = std::make_shared<SyncEntriesResponseHandler>(endpoints, userService);

    // register handlers
    std::map<std::string, std::shared_ptr<MessageHandler>> messageHandlers;
    messageHandlers["server.list.response"] = listServerDirsResponseHandler;
    messageHandlers["file.download.response"] = downloadFileResponseHandler;
    messageHandlers["file.sync.response"] = syncFileResponseHandler;
    messageHandlers["sync.list.response"] = syncEntriesResponseHandler;

    auto messageListener
            = std::unique_ptr<BlockingMessageListener>(new BlockingMessageListener(
                    messageStreamer, listenerLoop, messageHandlers));
    AsyncMessageListener asyncMessageListener(std::move(messageListener));
    asyncMessageListener.listen();

    // first sync between backup and primary
    Message message("server.list.request", "", "server.list.response");
    messageStreamer->send(message);

    while (listenerLoop.isOpen()){

    }
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

    auto replicaManagers = std::shared_ptr<ReplicaManagers>();
    auto listServerDirsHandler = std::make_shared<ListServerDirectoriesHandler>(fileRepository, replicaManagers);

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


