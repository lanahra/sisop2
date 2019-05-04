#include <iostream>
#include <iterator>
#include <memory>
#include <sstream>
#include <vector>
#include "application/DefaultPrinterService.h"
#include "application/DefaultUserService.h"
#include "infra/handler/DownloadFileCommandHandler.h"
#include "infra/handler/DownloadFileResponseHandler.h"
#include "infra/handler/ExitCommandHandler.h"
#include "infra/handler/ListClientEntriesCommandHandler.h"
#include "infra/handler/ListServerEntriesCommandHandler.h"
#include "infra/handler/ListServerEntriesResponseHandler.h"
#include "infra/handler/RemoveFileCommandHandler.h"
#include "infra/handler/SaveFileHandler.h"
#include "infra/handler/SyncEndpoints.h"
#include "infra/handler/SyncEntriesResponseHandler.h"
#include "infra/handler/SyncFileResponseHandler.h"
#include "infra/handler/UploadFileCommandHandler.h"
#include "infra/messaging/AsyncMessageListener.h"
#include "infra/messaging/BlockingCommandListener.h"
#include "infra/messaging/BlockingMessageListener.h"
#include "infra/messaging/Message.h"
#include "infra/messaging/OpenListenerLoop.h"
#include "infra/messaging/Socket.h"
#include "infra/messaging/SocketMessageStreamer.h"
#include "infra/messaging/TcpSocket.h"
#include "infra/repository/DefaultUserRepository.h"
#include "infra/repository/SystemFileRepository.h"

struct config {
    std::string username;
    std::string address;
    int port;
};

struct config parseArgs(int argc, char** argv);

int main(int argc, char** argv) {
    struct config config = parseArgs(argc, argv);

    auto socket = std::make_shared<TcpSocket>();
    socket->connect(config.address, config.port);

    auto messageStreamer = std::make_shared<SocketMessageStreamer>(socket);
    OpenListenerLoop listenerLoop;

    SystemFileRepository fileRepository;
    DefaultUserRepository userRepository(fileRepository);
    DefaultUserService userService(userRepository, fileRepository);

    DefaultPrinterService printerService(std::cout);

    // message handlers
    auto listServerResponseHandler
        = std::make_shared<ListServerEntriesResponseHandler>(printerService);
    auto downloadFileResponseHandler
        = std::make_shared<DownloadFileResponseHandler>(userService, std::cout);
    auto syncFileResponseHandler = std::make_shared<SyncFileResponseHandler>(
        config.username, userService);

    SyncEndpoints endpoints
        = SyncEndpoints::Builder()
              .withListEntries("file.list.request", "sync.list.response")
              .withDownloadFile("file.download.request", "file.sync.response")
              .withRemoveFile("file.remove.request")
              .withUploadFile("file.upload.request")
              .build();
    auto syncEntriesResponseHandler
        = std::make_shared<SyncEntriesResponseHandler>(
            config.username, endpoints, userService);

    std::map<std::string, std::shared_ptr<MessageHandler>> messageHandlers;
    messageHandlers["file.list.response"] = listServerResponseHandler;
    messageHandlers["file.download.response"] = downloadFileResponseHandler;
    messageHandlers["file.sync.response"] = syncFileResponseHandler;
    messageHandlers["sync.list.response"] = syncEntriesResponseHandler;

    auto messageListener
        = std::unique_ptr<BlockingMessageListener>(new BlockingMessageListener(
            messageStreamer, listenerLoop, messageHandlers));
    AsyncMessageListener asyncMessageListener(std::move(messageListener));
    asyncMessageListener.listen();

    // command handlers
    auto exitCommandHandler = std::make_shared<ExitCommandHandler>();
    auto listClientCommandHandler
        = std::make_shared<ListClientEntriesCommandHandler>(
            config.username, userService, printerService);
    auto listServerCommandHandler
        = std::make_shared<ListServerEntriesCommandHandler>(
            config.username, "file.list.request", "file.list.response");
    auto syncCommandHandler = std::make_shared<ListServerEntriesCommandHandler>(
        config.username, "file.list.request", "sync.list.response");
    auto removeFileCommandHandler = std::make_shared<RemoveFileCommandHandler>(
        config.username, "file.remove.request", std::cout);
    auto downloadFileCommandHandler
        = std::make_shared<DownloadFileCommandHandler>(config.username,
                                                       "file.download.request",
                                                       "file.download.response",
                                                       std::cout);
    auto uploadFileCommandHandler = std::make_shared<UploadFileCommandHandler>(
        config.username, "file.upload.request", userService, std::cout);

    std::map<std::string, std::shared_ptr<CommandHandler>> commandHandlers;
    commandHandlers["exit"] = exitCommandHandler;
    commandHandlers["list_client"] = listClientCommandHandler;
    commandHandlers["list_server"] = listServerCommandHandler;
    commandHandlers["delete"] = removeFileCommandHandler;
    commandHandlers["download"] = downloadFileCommandHandler;
    commandHandlers["upload"] = uploadFileCommandHandler;
    commandHandlers["get_sync_dir"] = syncCommandHandler;

    // start sync
    syncCommandHandler->handle({}, *messageStreamer);

    BlockingCommandListener commandListener(
        std::cin, listenerLoop, messageStreamer, commandHandlers);
    commandListener.listen();
}

struct config parseArgs(int argc, char** argv) {
    if (argc < 4) {
        std::cout << "username address port expected" << std::endl;
        exit(EXIT_FAILURE);
    } else {
        struct config config;
        std::stringstream arg;
        arg << argv[1];
        config.username = arg.str();
        arg.str("");
        arg << argv[2];
        config.address = arg.str();
        arg.str("");
        arg << argv[3];
        arg >> config.port;
        return config;
    }
}
