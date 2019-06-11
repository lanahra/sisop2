#ifndef SYNC_ENDPOINTS_H
#define SYNC_ENDPOINTS_H

#include <string>

class SyncEndpoints {
    std::string downloadFileOperation;
    std::string downloadFileResponse;
    std::string uploadFileOperation;
    std::string removeFileOperation;

  public:
    SyncEndpoints(std::string downloadFileOperation,
                  std::string downloadFileResponse,
                  std::string uploadFileOperation,
                  std::string removeFileOperation)
        : downloadFileOperation(downloadFileOperation),
          downloadFileResponse(downloadFileResponse),
          uploadFileOperation(uploadFileOperation),
          removeFileOperation(removeFileOperation){};

  public:
    class Builder;

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
    std::string downloadFileOperation;
    std::string downloadFileResponse;
    std::string uploadFileOperation;
    std::string removeFileOperation;

  public:
    Builder() = default;

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
        return SyncEndpoints(downloadFileOperation,
                             downloadFileResponse,
                             uploadFileOperation,
                             removeFileOperation);
    }
};

#endif