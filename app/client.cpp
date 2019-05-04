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

int main() {
    auto socket = std::make_shared<TcpSocket>();
    socket->connect("127.0.0.1", 8888);

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

    std::map<std::string, std::shared_ptr<MessageHandler>> messageHandlers;
    messageHandlers["file.list.response"] = listServerResponseHandler;
    messageHandlers["file.download.response"] = downloadFileResponseHandler;

    auto messageListener
        = std::unique_ptr<BlockingMessageListener>(new BlockingMessageListener(
            messageStreamer, listenerLoop, messageHandlers));
    AsyncMessageListener asyncMessageListener(std::move(messageListener));
    asyncMessageListener.listen();

    // command handlers
    auto exitCommandHandler = std::make_shared<ExitCommandHandler>();
    auto listClientCommandHandler
        = std::make_shared<ListClientEntriesCommandHandler>(
            "sixth", userService, printerService);
    auto listServerCommandHandler
        = std::make_shared<ListServerEntriesCommandHandler>(
            "sixth", "file.list.request", "file.list.response");
    auto syncCommandHandler
        = std::make_shared<ListServerEntriesCommandHandler>(
            "sixth", "file.list.request", "file.sync.response");
    auto removeFileCommandHandler = std::make_shared<RemoveFileCommandHandler>(
        "sixth", "file.remove.request", std::cout);
    auto downloadFileCommandHandler
        = std::make_shared<DownloadFileCommandHandler>("sixth",
                                                       "file.download.request",
                                                       "file.download.response",
                                                       std::cout);
    auto uploadFileCommandHandler
            = std::make_shared<UploadFileCommandHandler>("sixth",
                                                         "file.upload.request",
                                                         userService,
                                                         std::cout);

    std::map<std::string, std::shared_ptr<CommandHandler>> commandHandlers;
    commandHandlers["exit"] = exitCommandHandler;
    commandHandlers["list_client"] = listClientCommandHandler;
    commandHandlers["list_server"] = listServerCommandHandler;
    commandHandlers["delete"] = removeFileCommandHandler;
    commandHandlers["download"] = downloadFileCommandHandler;
    commandHandlers["get_sync_dir"] = syncCommandHandler;
    commandHandlers["upload"] = uploadFileCommandHandler;

    BlockingCommandListener commandListener(
        std::cin, listenerLoop, messageStreamer, commandHandlers);
    commandListener.listen();
}
