#include <map>
#include <memory>
#include "infra/messaging/TcpSocket.h"
#include "infra/messaging/OpenListenerLoop.h"
#include "infra/messaging/ConnectionListener.h"
#include "infra/messaging/AsyncMessageListenerFactory.h"
#include "infra/messaging/MessageHandler.h"
#include "infra/handler/EstablishSessionHandler.h"

int main() {
    // create handler for command.establish_session
    std::shared_ptr<MessageHandler> establishSessionHandler
        = std::make_shared<EstablishSessionHandler>();

    // register handlers
    std::map<std::string, std::shared_ptr<MessageHandler>> handlers;
    handlers["command.establish_session"] = establishSessionHandler;

    // factory for message listeners for every new connection
    OpenListenerLoop listenerLoop;
    AsyncMessageListenerFactory factory(listenerLoop, handlers);

    // starts listening for connections
    TcpSocket socket;
    ConnectionListener connectionListener(socket, listenerLoop, factory);
    connectionListener.listen(8888);
}
