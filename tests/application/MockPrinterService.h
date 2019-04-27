#ifndef MOCK_PRINTER_SERVICE_H
#define MOCK_PRINTER_SERVICE_H

#include <gmock/gmock.h>
#include <list>
#include "application/PrinterService.h"

class MockPrinterService : public PrinterService {
  public:
    MOCK_METHOD1(printEntries, void(std::list<FileEntry>));
};

#endif