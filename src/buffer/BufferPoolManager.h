#pragma once

#include "config.h"
#include "buffer/LruCache.h"
#include "page/Page.h"
#include "disk/DiskIOManager.h"
#include <list>
#include <unordered_map>
#include <atomic>
using std::list;
using std::unordered_map;
using std::atomic;

/**
 * @brief Load pages from disk and cache them in memory, pages on disk would exceed the amount in memory
 *        so we will use `least recently used` mechanism to swap out pages and flush them onto the disk
 * 
 * frame_id_t represents the id in memory, so it's limited to poolFrameSize, frame_id_t will be between 0 and poolFrameSize-1.
 * page_id_t represents a page on disk, so the page_id_t is highly relative with database's size, and it might be unlimited.
 * 
 */
class BufferPoolManager {
public:
    BufferPoolManager(size_t poolSize, page_id_t nextPage, DiskIOManager* ioManager);
    BufferPoolManager() = delete;
    ~BufferPoolManager();
    Page* getPage(page_id_t id);
    Page* newPage(page_id_t* id);
    bool flushPage(page_id_t id);
    bool deletePage(page_id_t id);
private:
    bool reserveFrame(frame_id_t*);
    const size_t poolFrameSize;
    Page* pool;
    atomic<page_id_t> nextPageId{0};
    LruCache* lruCache;
    DiskIOManager* diskMgr;
    list<frame_id_t> freeList;
    unordered_map<page_id_t, frame_id_t> slotsMap;
};