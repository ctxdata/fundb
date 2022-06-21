#pragma once
#include <cstddef>

// Disk storage
enum DiskEnum : size_t {
    PAGE_SIZE = 4 * 1024,
    EXTENT_SIZE = PAGE_SIZE * 1024,
    TABLESPACE_SIZE = EXTENT_SIZE * 64
};

// page id in FunDB, as same as page id on disk
typedef size_t page_id_t;

// frame id in buffer pool
typedef size_t frame_id_t;
