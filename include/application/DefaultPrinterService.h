#ifndef DEFAULT_PRINTER_SERVICE_H
#define DEFAULT_PRINTER_SERVICE_H

#include <list>
#include "PrinterService.h"

class DefaultPrinterService : public PrinterService {
    std::ostream& output;

    void printHeader();
    void printEntry(FileEntry entry);
    std::string formatTimestamp(time_t time);

  public:
    DefaultPrinterService(std::ostream& output): output(output) {};
    void printEntries(std::list<FileEntry> entries) override;
};

#endif