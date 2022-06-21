#include <iostream>
using std::cout;
using std::endl;

#include "config.h"

#include "disk/DiskIOManager.h"
#include "buffer/BufferPoolManager.h"

int main(int argc, char* argv[]) {
    DiskIOManager ioManager("fundb.db");
    BufferPoolManager poolMgr{64, &ioManager};
    page_id_t id;
    Page* page = poolMgr.newPage(&id);
    std::strncpy(page->data(), "Hello FunDB! A way to RDBMS from scratch.", DiskEnum::PAGE_SIZE);
    poolMgr.flushPage(0);
    return 0;
}