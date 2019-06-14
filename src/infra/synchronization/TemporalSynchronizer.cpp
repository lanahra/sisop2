//
// Created by christian on 11/06/19.
//

#include <thread>
#include <chrono>
#include "infra/synchronization/TemporalSynchronizer.h"

void TemporalSynchronizer::start() {
    while(listenerLoop.isOpen()){
        syncCommandHandler->handle({}, messageStreamer);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}