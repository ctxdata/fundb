#include "buffer/LruCache.h"

LruCache::LruCache(size_t num_pages) : sz(num_pages) {

}

bool LruCache::evict(frame_id_t* id) {
    std::lock_guard<mutex> guaud(mtx);
    if (q.size() > 0) {
        *id = q.front();
        q.pop_front();
        return true;
    }

    return false;
}

void LruCache::pin(const frame_id_t& id) {
    std::lock_guard<mutex> guaud(mtx);
    auto it = std::find(q.begin(), q.end(), id);
    if (it != q.end()) {
        q.erase(it);
    }
}

void LruCache::unpin(const frame_id_t& id) {
    std::lock_guard<mutex> guaud(mtx);
    if (q.size() < sz) {
        auto it = std::find(q.begin(), q.end(), id);
        if (it == q.end()) {
            q.push_back(id);
        }
    }
}

size_t LruCache::size() const {
    return q.size();
}
