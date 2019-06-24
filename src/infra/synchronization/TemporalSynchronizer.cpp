#include <thread>
#include <chrono>
#include "infra/synchronization/TemporalSynchronizer.h"

void TemporalSynchronizer::start() {
    while(listenerLoop.isOpen()){
        commandHandler->handle({}, messageStreamer);
        std::this_thread::sleep_for(std::chrono::milliseconds(sleepInMillis));
    }
}