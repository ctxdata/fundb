#include <iostream>
using std::cout;
using std::endl;

#include "config.h"

#include "disk/DiskIOManager.h"

int main(int argc, char* argv[]) {
    DiskIOManager ioManager("fundb.db");
    char* pageContent = new char[DiskEnum::PAGE_SIZE];
    strcpy(pageContent, "Hello fundb with gtest!!!!");
    ioManager.writePage(0, pageContent);
    return 0;
}