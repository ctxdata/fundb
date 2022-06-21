#include "DiskIOManager.h"

DiskIOManager::DiskIOManager(const string& db) : dbFile(db) {
    // open file
    dbStream.open(db, std::ios::binary | std::ios::in | std::ios::out | std::ios::app);
    dbStream.seekg(std::ios::end);
    pages = dbStream.tellg() / DiskEnum::PAGE_SIZE;
    dbStream.seekg(0);
}

DiskIOManager::~DiskIOManager() {
    if (dbStream.is_open()) {
        dbStream.close();
    }
}

size_t DiskIOManager::readPage(page_id_t pageId, char* dataOut, size_t pageCount) {
    if (dbStream.is_open()) {
        if (pageId + pageCount <= pages) {
            size_t pos = pageId * DiskEnum::PAGE_SIZE;
            size_t size = pageCount * DiskEnum::PAGE_SIZE;
            dbStream.seekg(pos);
            dbStream.read(dataOut, size);
            return size;
        } else {
            // warning, there are no enough pages for reading, there must be something wrong
        }
    }

    return 0;
}

size_t DiskIOManager::writePage(page_id_t pageId, const char* const dataIn, size_t pageCount) {
    if (dbStream.is_open()) {
        dbStream.seekg(pageId * DiskEnum::PAGE_SIZE);
        size_t size = pageCount * DiskEnum::PAGE_SIZE;
        dbStream.write(dataIn, size);
        dbStream.flush();

        if (pageId + pageCount > pages) {
            pages = pageId + pageCount;
        }
        return size;
    }

    return 0;
}
