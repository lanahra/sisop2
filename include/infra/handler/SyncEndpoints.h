#ifndef SYNC_ENDPOINTS_H
#define SYNC_ENDPOINTS_H

#include <string>

class SyncEndpoints {
    std::string listEntriesOperation;
    std::string listEntriesResponse;
    std::string downloadFileOperation;
    std::string downloadFileResponse;
    std::string uploadFileOperation;
    std::string removeFileOperation;

  public:
    SyncEndpoints(std::string listEntriesOperation,
                  std::string listEntriesResponse,
                  std::string downloadFileOperation,
                  std::string downloadFileResponse,
                  std::string uploadFileOperation,
                  std::string removeFileOperation)
        : listEntriesOperation(listEntriesOperation),
          listEntriesResponse(listEntriesResponse),
          downloadFileOperation(downloadFileOperation),
          downloadFileResponse(downloadFileResponse),
          uploadFileOperation(uploadFileOperation),
          removeFileOperation(removeFileOperation){};

  public:
    class Builder;

    std::string getListEntriesOperation() const {
        return listEntriesOperation;
    }

    std::string getListEntriesResponse() const {
        return listEntriesResponse;
    }
    std::string getDownloadFileOperation() const {
        return downloadFileOperation;
    }
    std::string getDownloadFileResponse() const {
        return downloadFileResponse;
    }
    std::string getUploadFileOperation() const {
        return uploadFileOperation;
    }
    std::string getRemoveFileOperation() const {
        return removeFileOperation;
    }
};

class SyncEndpoints::Builder {
    std::string listEntriesOperation;
    std::string listEntriesResponse;
    std::string downloadFileOperation;
    std::string downloadFileResponse;
    std::string uploadFileOperation;
    std::string removeFileOperation;

  public:
    Builder() = default;

    Builder& withListEntries(std::string operation, std::string response) {
        this->listEntriesOperation = operation;
        this->listEntriesResponse = response;
        return *this;
    }

    Builder& withDownloadFile(std::string operation, std::string response) {
        this->downloadFileOperation = operation;
        this->downloadFileResponse = response;
        return *this;
    }

    Builder& withUploadFile(std::string operation) {
        this->uploadFileOperation = operation;
        return *this;
    }

    Builder& withRemoveFile(std::string operation) {
        this->removeFileOperation = operation;
        return *this;
    }

    SyncEndpoints build() {
        return SyncEndpoints(listEntriesOperation,
                             listEntriesResponse,
                             downloadFileOperation,
                             downloadFileResponse,
                             uploadFileOperation,
                             removeFileOperation);
    }
};

#endif