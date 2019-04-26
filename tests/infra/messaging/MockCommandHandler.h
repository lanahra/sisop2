#ifndef MOCK_COMMAND_HANDLER_H
#define MOCK_COMMAND_HANDLER_H

#include <gmock/gmock.h>
#include "infra/messaging/CommandHandler.h"

class MockCommandHandler : public CommandHandler {
  public:
    MOCK_METHOD2(handle, void(std::vector<std::string>, MessageStreamer&));
};

#endif