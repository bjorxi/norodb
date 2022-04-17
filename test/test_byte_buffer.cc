#include <iostream>

#include <gtest/gtest.h>

#include "byte_buffer.h"



TEST(ByteBufferContruction, DEFAULT) {
  norodb::ByteBuffer buff;
  ASSERT_EQ(buff.size(), 0);
  ASSERT_EQ(buff.capacity(), DEFAULT_CAPACITY);
}

TEST(ByteBufferContruction, INIT_CAPACITY_PROVIDED) {
  norodb::ByteBuffer buff(99);

  ASSERT_EQ(buff.size(), 0);
  ASSERT_EQ(buff.capacity(), 99);
}


// Test that ByteBuffer grows as expected
TEST(ByteBufferGrow, NO_PARAMS) {
  norodb::ByteBuffer buff;
  ASSERT_EQ(buff.size(), 0);
  ASSERT_EQ(buff.capacity(), DEFAULT_CAPACITY);
  buff.grow();
  ASSERT_EQ(buff.size(), 0);
  ASSERT_EQ(buff.capacity(), DEFAULT_CAPACITY*2);
}


// Test that ByteBuffer grows as expected
TEST(ByteBufferGrow, GROW_CAPACITY_PROVIDED) {
  norodb::ByteBuffer buff;
  ASSERT_EQ(buff.size(), 0);
  ASSERT_EQ(buff.capacity(), DEFAULT_CAPACITY);
  buff.grow(1001);
  ASSERT_EQ(buff.size(), 0);
  ASSERT_EQ(buff.capacity(), 1001) << "Expected capacity: " << 1257 << ", real: " << buff.capacity();
}

TEST(ByteBufferPut, Put) {
  norodb::ByteBuffer buff;
  buff.put('a');
  ASSERT_EQ(buff.size(), 1);
  ASSERT_EQ(buff.to_string(), "a");
}


TEST(ByteBufferPut, PutWillGrow) {
  norodb::ByteBuffer buff(1);
  buff.put(static_cast<uint8_t>('a'));
  ASSERT_EQ(buff.size(), 1);
  ASSERT_EQ(buff.capacity(), 1);
  
  buff.put(static_cast<uint8_t>('b'));
  ASSERT_EQ(buff.size(), 2);
  ASSERT_EQ(buff.capacity(), 2);
  ASSERT_EQ(buff.to_string(), "ab");
}


int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
