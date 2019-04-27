#include <iostream>
#include <iterator>
#include <memory>
#include <sstream>
#include <vector>
#include "application/DefaultPrinterService.h"
#include "application/DefaultUserService.h"
#include "infra/handler/ExitCommandHandler.h"
#include "infra/handler/ListClientEntriesCommandHandler.h"
#include "infra/handler/ListServerEntriesCommandHandler.h"
#include "infra/handler/ListServerEntriesResponseHandler.h"
#include "infra/handler/RemoveFileCommandHandler.h"
#include "infra/messaging/AsyncMessageListener.h"
#include "infra/messaging/BlockingCommandListener.h"
#include "infra/messaging/BlockingMessageListener.h"
#include "infra/messaging/Message.h"
#include "infra/messaging/OpenListenerLoop.h"
#include "infra/messaging/Socket.h"
#include "infra/messaging/SocketMessageStreamer.h"
#include "infra/messaging/TcpSocket.h"
#include "infra/repository/SystemFileRepository.h"
#include "server/SystemClock.h"

int main() {
    auto socket = std::make_shared<TcpSocket>();
    socket->connect("127.0.0.1", 8888);

    auto messageStreamer = std::make_shared<SocketMessageStreamer>(socket);
    OpenListenerLoop listenerLoop;

    SystemClock clock;
    SystemFileRepository fileRepository(clock);
    UserFactory userFactory(fileRepository);
    DefaultUserService userService(userFactory);

    DefaultPrinterService printerService(std::cout);

    // message handlers
    auto listServerResponseHandler
        = std::make_shared<ListServerEntriesResponseHandler>(printerService);

    std::map<std::string, std::shared_ptr<MessageHandler>> messageHandlers;
    messageHandlers["file.list.response"] = listServerResponseHandler;

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
    auto removeFileCommandHandler = std::make_shared<RemoveFileCommandHandler>(
        "sixth", "file.remove.request", std::cout);

    std::map<std::string, std::shared_ptr<CommandHandler>> commandHandlers;
    commandHandlers["exit"] = exitCommandHandler;
    commandHandlers["list_client"] = listClientCommandHandler;
    commandHandlers["list_server"] = listServerCommandHandler;
    commandHandlers["delete"] = removeFileCommandHandler;

    BlockingCommandListener commandListener(
        std::cin, listenerLoop, messageStreamer, commandHandlers);
    commandListener.listen();
}
