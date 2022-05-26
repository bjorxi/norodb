#include <gtest/gtest.h>

#include <iostream>

#include "row.h"

TEST(RowHeader, Serialize) {
  norodb::RowHeader h(1, 2, 3, 4, 5);
  auto bb = h.serialize();
  ASSERT_EQ(bb->size(), 22);
}


TEST(RowHeader, Deserialize) {
  norodb::RowHeader h1(1, 2, 3, 4, 5);
  auto bb = h1.serialize();

  auto h2 = norodb::RowHeader::deserialize(*bb);

  ASSERT_EQ(h2->get_seq_num(), 5);
  ASSERT_EQ(h2->get_key_size(), 3);
  ASSERT_EQ(h2->get_val_size(), 4);
}

TEST(Row, Serialize) {
  norodb::RowHeader h(1, 2, 3, 4, 5);
  norodb::ByteBuffer key("key");
  norodb::ByteBuffer val("val");

  norodb::Row r(&key, &val);
  r.set_header(&h);
  auto bb = r.serialize();
  ASSERT_EQ(bb->size(), 28);
}

TEST(Row, Deserialize) {
  norodb::RowHeader h(1, 2, 3, 4, 5);
  norodb::ByteBuffer key("key");
  norodb::ByteBuffer val("val");

  norodb::Row r1(&key, &val);
  r1.set_header(&h);
  auto bb = r1.serialize();

  auto h2 = norodb::RowHeader::deserialize(*bb);
  auto r2 = norodb::Row::deserialize(*bb, h2->get_key_size(), h2->get_val_size());
  r2->set_header(h2);

  ASSERT_EQ(r2->get_key()->to_string(), "key");
  ASSERT_EQ(r2->get_val()->to_string(), "val");
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
