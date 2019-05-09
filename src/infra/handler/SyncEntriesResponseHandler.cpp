#include "infra/handler/SyncEntriesResponseHandler.h"
#include "infra/handler/ListFileEntriesResponse.h"

#include <infra/handler/DownloadFileRequest.h>
#include <infra/handler/RemoveFileRequest.h>
#include <infra/handler/UploadFileRequest.h>
#include <sstream>

void SyncEntriesResponseHandler::handle(Message message,
                                        MessageStreamer& messageStreamer) {
    ListFileEntriesResponse response = deserializeMessage(message.getBody());
    std::list<SyncOperation> operations
        = service.syncUser(username, response.getEntries());
    std::list<Message> messages = messagesFor(operations);
    sendMessages(messages, messageStreamer);
}

ListFileEntriesResponse SyncEntriesResponseHandler::deserializeMessage(
    std::string body) {
    std::stringstream serialized(body);
    ListFileEntriesResponse response;
    serialized >> response;
    return response;
}

std::list<Message> SyncEntriesResponseHandler::messagesFor(
    std::list<SyncOperation> operations) {
    std::list<Message> messages;
    for (SyncOperation operation : operations) {
        switch (operation.getOperation()) {
            case SyncOperation::DOWNLOAD:
                messages.push_back(downloadMessageFor(operation.getFilename()));
                break;
            case SyncOperation::UPLOAD:
                messages.push_back(uploadMessageFor(operation.getFilename()));
                break;
            case SyncOperation::DELETE:
                messages.push_back(deleteMessageFor(operation.getFilename()));
                break;
        }
    }
    messages.push_back(listEntriesMessage());
    return messages;
}

Message SyncEntriesResponseHandler::downloadMessageFor(std::string filename) {
    DownloadFileRequest request(username, filename);
    std::stringstream serialized;
    serialized << request;
    return Message(endpoints.getDownloadFileOperation(),
                   serialized.str(),
                   endpoints.getDownloadFileResponse());
}

Message SyncEntriesResponseHandler::uploadMessageFor(std::string filename) {
    File file = service.getFile(username, filename);
    UploadFileRequest request(username, file);
    std::stringstream serialized;
    serialized << request;
    return Message(endpoints.getUploadFileOperation(), serialized.str());
}

Message SyncEntriesResponseHandler::deleteMessageFor(std::string filename) {
    RemoveFileRequest request(username, filename);
    std::stringstream serialized;
    serialized << request;
    return Message(endpoints.getRemoveFileOperation(), serialized.str());
}

Message SyncEntriesResponseHandler::listEntriesMessage() {
    return Message(endpoints.getListEntriesOperation(),
                   username,
                   endpoints.getListEntriesResponse());
}

void SyncEntriesResponseHandler::sendMessages(
    std::list<Message> messages,
    MessageStreamer& messageStreamer) {
    for (Message message : messages) {
        messageStreamer.send(message);
    }
}