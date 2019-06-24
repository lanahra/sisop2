#include <infra/handler/DownloadFileResponseHandler.h>
#include <infra/handler/ListServerDirectoriesRequest.h>
#include <infra/handler/ListServerDirectoriesResponse.h>
#include <infra/handler/ListServerDirectoriesResponseHandler.h>
#include <infra/handler/SyncEndpoints.h>
#include <infra/handler/SyncEntriesResponseHandler.h>
#include <infra/handler/SyncFileResponseHandler.h>
#include <infra/handler/UpdateBackupsListHandler.h>
#include <chrono>
#include <map>
#include <memory>
#include <sstream>
#include <thread>
#include "application/DefaultUserService.h"
#include "infra/handler/DownloadFileHandler.h"
#include "infra/handler/IpClientHandler.h"
#include "infra/handler/ListFileEntriesHandler.h"
#include "infra/handler/ListServerDirectoriesHandler.h"
#include "infra/handler/RemoveFileHandler.h"
#include "infra/handler/SaveFileHandler.h"
#include "infra/messaging/AsyncMessageListener.h"
#include "infra/messaging/AsyncMessageListenerFactory.h"
#include "infra/messaging/BlockingMessageListener.h"
#include "infra/messaging/ConnectionListener.h"
#include "infra/messaging/MessageHandler.h"
#include "infra/messaging/OpenListenerLoop.h"
#include "infra/messaging/SecondarySocket.h"
#include "infra/messaging/SocketMessageStreamer.h"
#include "infra/messaging/TcpSocket.h"
#include "infra/repository/DefaultUserRepository.h"
#include "infra/repository/SystemFileRepository.h"
#include "infra/synchronization/DefaultKeyLock.h"
#include "server/ServerDescription.h"

void runServer(struct ServerDescription self,
               struct ServerDescription primary) {
    bool isPrimary = self == primary;

    SystemFileRepository fileRepository;
    DefaultUserRepository userRepository(fileRepository);
    DefaultKeyLock keyLock;
    DefaultUserService userService(userRepository, fileRepository, keyLock);
    std::list<std::string> clientList;

    // create handler for command.establish_session
    auto listFileEntriesHandler
        = std::make_shared<ListFileEntriesHandler>(userService);

    auto downloadFileHandler
        = std::make_shared<DownloadFileHandler>(userService);

    ReplicaManagers replicaManagers;
    auto removeFileHandler
        = std::make_shared<RemoveFileHandler>(userService, replicaManagers);

    auto saveFileHandler
        = std::make_shared<SaveFileHandler>(userService, replicaManagers);

    auto listServerDirsHandler = std::make_shared<ListServerDirectoriesHandler>(
        fileRepository, replicaManagers);

    auto ipClientHandler
        = std::make_shared<IpClientHandler>(replicaManagers, clientList);

    // register handlers
    std::map<std::string, std::shared_ptr<MessageHandler>> handlers;
    handlers["file.list.request"] = listFileEntriesHandler;
    handlers["file.download.request"] = downloadFileHandler;
    handlers["file.remove.request"] = removeFileHandler;
    handlers["file.upload.request"] = saveFileHandler;
    handlers["server.list.request"] = listServerDirsHandler;
    handlers["server.ip.request"] = ipClientHandler;

    auto listServerDirsResponseHandler
        = std::make_shared<ListServerDirectoriesResponseHandler>();
    auto downloadFileResponseHandler
        = std::make_shared<DownloadFileResponseHandler>(userService, std::cout);
    auto syncFileResponseHandler
        = std::make_shared<SyncFileResponseHandler>(userService);
    SyncEndpoints endpoints
        = SyncEndpoints::Builder()
              .withDownloadFile("file.download.request", "file.sync.response")
              .withRemoveFile("file.remove.request")
              .withUploadFile("file.upload.request")
              .build();
    auto syncEntriesResponseHandler
        = std::make_shared<SyncEntriesResponseHandler>(endpoints, userService);
    auto updateBackupsListHandler
        = std::make_shared<UpdateBackupsListHandler>(replicaManagers);

    handlers["server.list.response"] = listServerDirsResponseHandler;
    handlers["file.download.response"] = downloadFileResponseHandler;
    handlers["file.sync.response"] = syncFileResponseHandler;
    handlers["sync.list.response"] = syncEntriesResponseHandler;
    handlers["backup.servers.update"] = updateBackupsListHandler;

    // factory for message listeners for every new connection
    OpenListenerLoop listenerLoop;
    AsyncMessageListenerFactory factory(listenerLoop, handlers);

    TcpSocket socket;
    ConnectionListener connectionListener(socket, listenerLoop, factory);

    if (isPrimary) {
        // starts listening for connections
        connectionListener.listen(self.port);
    } else {
        auto socket = std::make_shared<SecondarySocket>(
            self, 10, replicaManagers, factory, connectionListener, clientList);
        socket->connect(primary.address, primary.port);
        auto messageStreamer = std::make_shared<SocketMessageStreamer>(socket);

        // first sync between backup and primary
        ListServerDirectoriesRequest listServerDirectoriesRequest(self.address,
                                                                  self.port);
        std::stringstream serialized;
        serialized << listServerDirectoriesRequest;
        Message message(
            "server.list.request", serialized.str(), "server.list.response");
        messageStreamer->send(message);

        auto messageListener = std::unique_ptr<BlockingMessageListener>(
            new BlockingMessageListener(
                messageStreamer, listenerLoop, handlers));
        messageListener->listen();

        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(10));
        }
    }
}

int main(int argc, char** argv) {
    struct ServerDescription self, primary;
    if (argc < 2) {
        std::cout << "address and port number expected" << std::endl;
        exit(EXIT_FAILURE);
    } else {
        std::stringstream arg;
        arg << argv[1];
        self.address = arg.str();
        arg.str("");
        arg << argv[2];
        arg >> self.port;

        if (argc == 5) {
            std::stringstream arg;
            arg << argv[3];
            primary.address = arg.str();
            arg.str("");
            arg << argv[4];
            arg >> primary.port;
        } else {
            primary = self;
        }

        runServer(self, primary);
    }
}
