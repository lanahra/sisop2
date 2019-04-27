#include "application/DefaultPrinterService.h"
#include <iomanip>
#include <sstream>

void DefaultPrinterService::printEntries(std::list<FileEntry> entries) {
    printHeader();
    for (FileEntry entry : entries) {
        printEntry(entry);
    }
    output.flush();
}

void DefaultPrinterService::printHeader() {
    output << std::left << std::setw(24) << "last modified" << std::setw(24)
           << "last accessed" << std::setw(24) << "last changed"
           << "file" << std::endl;
}

void DefaultPrinterService::printEntry(FileEntry entry) {
    output << std::setw(24)
           << formatTimestamp(entry.getTimestamps().getLastModification())
           << std::setw(24)
           << formatTimestamp(entry.getTimestamps().getLastAccess())
           << std::setw(24)
           << formatTimestamp(entry.getTimestamps().getLastChange())
           << entry.getName() << std::endl;
}

std::string DefaultPrinterService::formatTimestamp(time_t time) {
    std::stringstream format;
    format << std::put_time(localtime(&time), "%Y-%m-%d %X");
    return format.str();
}
