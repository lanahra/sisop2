#ifndef SYNC_OPERATION_H
#define SYNC_OPERATION_H

class SyncOperation {
  public:
    enum Operation { DOWNLOAD, UPLOAD, DELETE };
    SyncOperation(Operation operation, std::string filename)
        : operation(operation), filename(filename){};

    Operation getOperation() {
        return operation;
    }

    std::string getFilename() {
        return filename;
    }

    friend bool operator==(const SyncOperation& self,
                           const SyncOperation& other) {
        return self.operation == other.operation
            && self.filename == other.filename;
    }

  private:
    Operation operation;
    std::string filename;
};

#endif