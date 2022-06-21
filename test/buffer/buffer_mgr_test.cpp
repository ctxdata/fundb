#include "gtest/gtest.h"
#include "buffer/BufferPoolManager.h"

const static std::string DBFILE_NAME = {"test.db"};

class BufferPoolMgrTest : public ::testing::Test {
 protected:
  // This function is called before every test.
  void SetUp() override {
    remove(DBFILE_NAME.c_str());
  }

  // This function is called after every test.
  void TearDown() override {
    remove(DBFILE_NAME.c_str());
  };
};

TEST_F(BufferPoolMgrTest, BasicTest) {
    DiskIOManager ioManager{DBFILE_NAME};
    BufferPoolManager poolMgr{8, 0, &ioManager};

    EXPECT_EQ(nullptr, poolMgr.getPage(0));
    EXPECT_FALSE(poolMgr.flushPage(0));

    page_id_t id;

    Page* page = poolMgr.newPage(&id);
    EXPECT_NE(nullptr, page);
    EXPECT_EQ(id, 0);

    Page* page2 = poolMgr.newPage(&id);
    EXPECT_NE(nullptr, page);
    EXPECT_EQ(id, 1);

    std::strncpy(page->data(), "Hello FunDB Buffer pool", DiskEnum::PAGE_SIZE);
    page->data()[DiskEnum::PAGE_SIZE-2] = 0x55;
    page->data()[DiskEnum::PAGE_SIZE-1] = 0xAA;

    bool flushed = poolMgr.flushPage(0);
    EXPECT_TRUE(flushed);

    page = poolMgr.getPage(0);
    EXPECT_NE(nullptr, page);
    char* data = page->data();
    EXPECT_EQ(0x55, (unsigned char)data[DiskEnum::PAGE_SIZE-2]);
    EXPECT_EQ(0xAA, (unsigned char)data[DiskEnum::PAGE_SIZE-1]);

    EXPECT_EQ(0, std::strncmp(data, "Hello FunDB Buffer pool", DiskEnum::PAGE_SIZE));

    EXPECT_EQ(true, poolMgr.deletePage(0));
}