#ifndef PRINTER_SERVICE_H
#define PRINTER_SERVICE_H

#include <list>
#include "server/FileEntry.h"

class PrinterService {
  public:
    virtual void printEntries(std::list<FileEntry> entries) = 0;
};

#endif