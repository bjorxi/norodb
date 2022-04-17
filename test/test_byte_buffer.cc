#include <gtest/gtest.h>

#include "byte_buffer.h"



TEST(ByteBufferContruction, BLA) {
  norodb::ByteBuffer buff;


  ASSERT_EQ(buff.size(), 0);
}


int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
