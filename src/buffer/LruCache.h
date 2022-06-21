#pragma once

#include <list>
#include <mutex>
#include "config.h"

using std::list;
using std::mutex;

class LruCache {
public:
    /**
     * @brief Construct a new Lru Cache object
     * 
     * @param num_pages 
     */
    explicit LruCache(size_t num_pages);
    /**
     * @brief evict a least recently used frame from cache list
     * 
     * @param id: frame id evicted
     * @return true: if a frame is evicted
     * @return false: if no frame is evicted
     */
    bool evict(frame_id_t* id);

    /**
     * @brief pick up a frame from cache list and pin it, hence this pinned frame cannot be evicted
     * 
     * @param id: the frame id is being pinned
     */
    void pin(const frame_id_t& id);

    /**
     * @brief Unpin a frame which means handing over the control back to cache, 
     *        so that frame can be evicted if it's least used in the future.
     * 
     * @param id 
     */
    void unpin(const frame_id_t& id);

    /**
     * @brief return the size of frames managed by LruCache, in other words it indicates how many frames can be reused
     * 
     * @return size_t
     */
    size_t size() const;
private:
    std::list<frame_id_t> q;
    const size_t sz;
    std::mutex mtx;
};