#include "gtest/gtest.h"
#include "buffer/LruCache.h"

class LruCacheTest : public ::testing::Test {
 protected:
  // This function is called before every test.
  void SetUp() override {
    //remove(DBFILE_NAME.c_str());
  }

  // This function is called after every test.
  void TearDown() override {
    //remove(DBFILE_NAME.c_str());
  };
};

TEST_F(LruCacheTest, BasicTest) {
    LruCache lruCache{10};
    frame_id_t id;
    bool evicted = lruCache.evict(&id);

    EXPECT_EQ(evicted, false);

    for (auto id : {1,2,3,4,5,6,7,8,9,10}) {
        lruCache.unpin(id);
    }

    EXPECT_EQ(10, lruCache.size());

    lruCache.unpin(11);
    EXPECT_EQ(10, lruCache.size());

    lruCache.pin(11);
    EXPECT_EQ(10, lruCache.size());

    evicted = lruCache.evict(&id);
    EXPECT_EQ(evicted, true);
    EXPECT_EQ(id, 1);
    EXPECT_EQ(9, lruCache.size());

    lruCache.pin(2);
    EXPECT_EQ(8, lruCache.size());

    evicted = lruCache.evict(&id);
    EXPECT_EQ(evicted, true);
    EXPECT_EQ(id, 3);
    EXPECT_EQ(7, lruCache.size());
}