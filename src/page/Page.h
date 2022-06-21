#pragma once

#include "config.h"

class Page {
public:
    char* data() {
        return d;
    }
    
    void reset() {
        memset(d, 0, DiskEnum::PAGE_SIZE);
    }
private:
    char d[DiskEnum::PAGE_SIZE];
};