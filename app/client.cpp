#include <iostream>
#include <iterator>
#include <memory>
#include <sstream>
#include <vector>
#include "infra/handler/ExitCommandHandler.h"
#include "infra/messaging/AsyncMessageListener.h"
#include "infra/messaging/BlockingCommandListener.h"
#include "infra/messaging/Message.h"
#include "infra/messaging/OpenListenerLoop.h"
#include "infra/messaging/Socket.h"
#include "infra/messaging/SocketMessageStreamer.h"
#include "infra/messaging/TcpSocket.h"

int main() {
    auto socket = std::make_shared<TcpSocket>();
    socket->connect("127.0.0.1", 8888);

    auto messageStreamer = std::make_shared<SocketMessageStreamer>(socket);

    auto exitHandler = std::make_shared<ExitCommandHandler>();

    std::map<std::string, std::shared_ptr<CommandHandler>> commandHandlers;
    commandHandlers["exit"] = exitHandler;

    OpenListenerLoop listenerLoop;
    BlockingCommandListener commandListener(
        std::cin, listenerLoop, messageStreamer, commandHandlers);

    commandListener.listen();
}
