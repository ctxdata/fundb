#include "buffer/BufferPoolManager.h"

BufferPoolManager::BufferPoolManager(size_t poolSize,
                                    page_id_t nextPage,
                                    DiskIOManager* ioManager) : poolFrameSize(poolSize), nextPageId(nextPage), diskMgr(ioManager) {
    pool = new Page[poolSize];
    lruCache = new LruCache(poolSize);

    for (auto i=0; i<poolSize; i++) {
        freeList.push_back(i);
    }
}

BufferPoolManager::~BufferPoolManager() {
    delete[] pool;
    delete lruCache;
}

bool BufferPoolManager::reserveFrame(frame_id_t* id) {
    // get a free frame from free list and load page from disk
    if (freeList.size() > 0) {
        *id = freeList.front();
        freeList.pop_front();
    } else {
        if (!lruCache->evict(id)) {
            // return nullptr or throw "out of buffer pages" error
            return false;
        }
    }
    return true;
}

Page* BufferPoolManager::getPage(page_id_t id) {
    if (id < nextPageId) {
        if (slotsMap.find(id) != slotsMap.end()) {
            return pool + slotsMap[id];
        }

        // get a free frame from free list and load page from disk
        frame_id_t frameId;
        if (!reserveFrame(&frameId)) {
            return nullptr;
        }

        Page* page = pool + frameId;
        page->reset();
        diskMgr->readPage(id, page->data());
        lruCache->pin(frameId);
        slotsMap[id] = frameId;
        return page;
    }
    return nullptr;
}

Page* BufferPoolManager::newPage(page_id_t* id) {
    frame_id_t frameId;
    if (!reserveFrame(&frameId)) {
        return nullptr;
    }

    *id = nextPageId.fetch_add(1);
    Page* page = pool + frameId;
    page->reset();
    lruCache->pin(frameId);
    slotsMap[*id] = frameId;
    return page;
}

bool BufferPoolManager::flushPage(page_id_t id) {
    if (slotsMap.find(id) == slotsMap.end()) {
        return false;
    }

    frame_id_t frameId = slotsMap[id];
    Page* page = pool + frameId;
    diskMgr->writePage(id, page->data());
    lruCache->unpin(frameId);
    slotsMap.erase(id);
    freeList.push_back(frameId);

    return true;
}

bool BufferPoolManager::deletePage(page_id_t id) {
    return true;
}
