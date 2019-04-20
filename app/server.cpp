#include <map>
#include <memory>
#include "infra/messaging/TcpSocket.h"
#include "infra/messaging/OpenListenerLoop.h"
#include "infra/messaging/ConnectionListener.h"
#include "infra/messaging/AsyncMessageListenerFactory.h"
#include "infra/messaging/MessageHandler.h"
#include "infra/handler/ListFileEntriesHandler.h"
#include "infra/repository/SystemFileRepository.h"
#include "application/UserFactory.h"
#include "application/DefaultUserService.h"

int main() {
    SystemFileRepository fileRepository;
    UserFactory userFactory(fileRepository);
    DefaultUserService userService(userFactory);

    // create handler for command.establish_session
    std::shared_ptr<MessageHandler> listFileEntriesHandler 
        = std::make_shared<ListFileEntriesHandler>(userService);

    // register handlers
    std::map<std::string, std::shared_ptr<MessageHandler>> handlers;
    handlers["file.list.request"] = listFileEntriesHandler;

    // factory for message listeners for every new connection
    OpenListenerLoop listenerLoop;
    AsyncMessageListenerFactory factory(listenerLoop, handlers);

    // starts listening for connections
    TcpSocket socket;
    ConnectionListener connectionListener(socket, listenerLoop, factory);
    connectionListener.listen(8888);
}
