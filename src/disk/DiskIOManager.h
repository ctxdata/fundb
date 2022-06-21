#pragma once
#include <string>
#include <fstream>

#include "../config.h"

using std::string;
using std::fstream;

class DiskIOManager {
private:
    string dbFile;
    size_t count;
    fstream dbStream;
public:
    DiskIOManager(const string& db);
    ~DiskIOManager();
    size_t pages() const {
        return this->count;
    }
    size_t readPage(page_id_t pageId, char* dataOut, size_t pageCount = 1);
    size_t writePage(page_id_t pageId, const char* const dataIn, size_t pageCount = 1);
};
