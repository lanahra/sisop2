#ifndef SISOP2_UPDATEBACKUPSLISTREQUEST_H
#define SISOP2_UPDATEBACKUPSLISTREQUEST_H

#include "../../server/ServerDescription.h"
#include <list>
#include <iostream>

class UpdateBackupsListRequest{
    std::list<struct ServerDescription> backupsDescriptions;

  public:
    UpdateBackupsListRequest(){};
    UpdateBackupsListRequest(std::list<ServerDescription> backupsDescriptions)
    : backupsDescriptions(backupsDescriptions){};

    std::list<struct ServerDescription> getBackupsDescriptions(){return backupsDescriptions;};

    friend bool operator==(const UpdateBackupsListRequest& self,
                           const UpdateBackupsListRequest& other) {
        return self.backupsDescriptions.size() == other.backupsDescriptions.size();
    }

    friend std::ostream& operator<<(std::ostream& out,
                                    const UpdateBackupsListRequest& self) {
        out << self.backupsDescriptions.size();
        for(struct ServerDescription backupDescription : self.backupsDescriptions){
            out << ",";
            out << backupDescription.address.size() << "," << backupDescription.address << ",";
            out << backupDescription.port;
        }
        return out;
    }

    friend std::istream& operator>>(std::istream& in, UpdateBackupsListRequest& self) {
        size_t size;
        in >> size;
        for(int i = 0; i < static_cast<int>(size); i++){
            in.ignore(1, ',');
            size_t addressSize;
            in >> addressSize;
            in.ignore(1, ',');

            struct ServerDescription serverDescription;
            serverDescription.address.resize(addressSize);
            in.read(&serverDescription.address[0], addressSize);
            in.ignore(1, ',');

            size_t port;
            in >> port;
            serverDescription.port = static_cast<int>(port);

            self.backupsDescriptions.push_back(serverDescription);
        }
        return in;
    }
};

#endif
