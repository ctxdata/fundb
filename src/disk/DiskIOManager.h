#pragma once
#include <string>
#include <fstream>

#include "../config.h"

using std::string;
using std::fstream;

class DiskIOManager {
private:
    string dbFile;
    size_t pages;
    fstream dbStream;
public:
    DiskIOManager(const string& db);
    ~DiskIOManager();
    size_t readPage(size_t pageNum, char* dataOut, size_t pageCount = 1);
    size_t writePage(size_t pageNum, const char* const dataIn, size_t pageCount = 1);
};
