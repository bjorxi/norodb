#include <iostream>
#include <string>

#include <gtest/gtest.h>

#include "db_directory.h"


TEST(DBDirectoryConstruction, WithFsPath) {
  fs::path p("abc");
  norodb::DBDirectory db_dir(p);

  ASSERT_EQ(db_dir.get_path(), "abc");
  ASSERT_EQ(db_dir.get_data_dir(), "abc/data");
  ASSERT_EQ(db_dir.get_index_dir(), "abc/index");

}

TEST(DBDirectoryConstruction, WithString) {
  std::string p = "random";
  norodb::DBDirectory db_dir(p);

  ASSERT_EQ(db_dir.get_path(), "random");
  ASSERT_EQ(db_dir.get_data_dir(), "random/data");
  ASSERT_EQ(db_dir.get_index_dir(), "random/index");

}

TEST(DBDirectoryConstruction, WithEmptyString) {
  std::string p = "";
  norodb::DBDirectory db_dir(p);

  ASSERT_EQ(db_dir.get_path(), "norodb");
  ASSERT_EQ(db_dir.get_data_dir(), "norodb/data");
  ASSERT_EQ(db_dir.get_index_dir(), "norodb/index");
}


int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
