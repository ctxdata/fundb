#include "gtest/gtest.h"
#include "disk/DiskIOManager.h"

const static std::string DBFILE_NAME = {"test.db"};

class DiskManagerTest : public ::testing::Test {
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

TEST_F(DiskManagerTest, ReadWritePageTest) {
    char buf[DiskEnum::PAGE_SIZE]{0};
    char data[DiskEnum::PAGE_SIZE]{0};
    std::string dbFile{DBFILE_NAME};

    DiskIOManager ioManager{dbFile};
    size_t bytesRead = ioManager.readPage(0, buf);
    EXPECT_EQ(0, bytesRead);

    std::strncpy(data, "FunDB Page Test.", sizeof(data));
    size_t bytesWritten = ioManager.writePage(0, data);
    EXPECT_EQ((size_t)DiskEnum::PAGE_SIZE, bytesWritten);

    std::memset(buf, 0, sizeof(buf));
    bytesRead = ioManager.readPage(0, buf);
    EXPECT_EQ(bytesRead, (size_t)DiskEnum::PAGE_SIZE);

    char twoPages[DiskEnum::PAGE_SIZE * 2];
    bytesRead = ioManager.readPage(0, twoPages, 2);
    EXPECT_EQ(0, bytesRead);
}