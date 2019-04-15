#include "infra/messaging/TcpSocket.h"

int main() {
    TcpSocket socket;
    socket.connect("127.0.0.1", 8888);

    // message serialization
    // length of command, command, length of serialized payload, payload
    // length of command.establish_session is 25
    // length of 4,name is 6
    // 4,name will be further deserialized in the handler for the command
    std::string message("25,command.establish_session,6,4,name");

    socket.writeInt(message.size());
    socket.write(message);
}
