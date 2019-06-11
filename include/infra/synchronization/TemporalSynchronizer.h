//
// Created by christian on 11/06/19.
//

#ifndef SISOP2_TEMPORALSYNCHRONIZER_H
#define SISOP2_TEMPORALSYNCHRONIZER_H


#include <infra/handler/ListServerEntriesCommandHandler.h>

class TemporalSynchronizer {
    std::shared_ptr<ListServerEntriesCommandHandler> syncCommandHandler;
    MessageStreamer& messageStreamer;

  public:
    TemporalSynchronizer(std::shared_ptr<ListServerEntriesCommandHandler> syncCommandHandler,
                 MessageStreamer& messageStreamer)
    :   syncCommandHandler(syncCommandHandler),
        messageStreamer(messageStreamer){};
    void start();
};


#endif