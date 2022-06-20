#pragma once
#include <cstddef>

// Disk storage
enum DiskEnum : size_t {
    PAGE_SIZE = 4 * 1024,
    EXTENT_SIZE = PAGE_SIZE * 1024
};