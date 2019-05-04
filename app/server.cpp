#include <server/SystemClock.h>
#include <map>
#include <memory>
#include <infra/handler/SaveFileHandler.h>
#include "application/DefaultUserService.h"
#include "application/UserFactory.h"
#include "infra/handler/DownloadFileHandler.h"
#include "infra/handler/ListFileEntriesHandler.h"
#include "infra/handler/RemoveFileHandler.h"
#include "infra/messaging/AsyncMessageListenerFactory.h"
#include "infra/messaging/ConnectionListener.h"
#include "infra/messaging/MessageHandler.h"
#include "infra/messaging/OpenListenerLoop.h"
#include "infra/messaging/TcpSocket.h"
#include "infra/repository/SystemFileRepository.h"

int main() {
    SystemFileRepository fileRepository;
    UserFactory userFactory(fileRepository);
    DefaultUserService userService(userFactory, fileRepository);

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
    connectionListener.listen(8888);
}
