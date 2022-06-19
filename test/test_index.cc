#include <gtest/gtest.h>

#include <iostream>

#include "index.h"
#include "byte_buffer.h"

TEST(Index, PutGet) {
  norodb::ByteBuffer key1("1");
  norodb::IndexEntry entry1(1,1,1,1);

  norodb::ByteBuffer key2("2");
  norodb::IndexEntry entry2(2,2,2,2);

  norodb::ByteBuffer key3("3");
  norodb::IndexEntry entry3(3,3,3,3);

  norodb::DBIndex index;

  index.put(key1, entry1);
  index.put(key2, entry2);
  index.put(key3, entry3);

  ASSERT_EQ(index.get(key1).get_file_id(), 1);
  ASSERT_EQ(index.get(key3).get_val_size(), 3);
}

TEST(Index, IndexEntrySerializeDeserialize) {
  norodb::IndexEntry entry1(1,2,3,4);
  auto buff1 = entry1.serialize();
  auto entry1_new = norodb::IndexEntry::deserialize(*buff1);

  ASSERT_EQ(entry1_new->get_file_id(), 1);


  norodb::IndexEntry entry2(13,23,19,17);
  auto buff2 = entry2.serialize();
  auto entry2_new = norodb::IndexEntry::deserialize(*buff2);

  ASSERT_EQ(entry2_new->get_file_id(), 13);
  ASSERT_EQ(entry2_new->get_val_offset(), 23);
  ASSERT_EQ(entry2_new->get_val_size(), 19);
  ASSERT_EQ(entry2_new->get_seq_num(), 17);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
