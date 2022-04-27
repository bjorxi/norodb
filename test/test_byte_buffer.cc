#include <gtest/gtest.h>

#include <iostream>

#include "byte_buffer.h"

TEST(ByteBufferContruction, DEFAULT) {
  norodb::ByteBuffer buff;
  ASSERT_EQ(buff.get_wpos(), 0);
  ASSERT_EQ(buff.get_rpos(), 0);
  ASSERT_EQ(buff.size(), 0);
  ASSERT_EQ(buff.capacity(), DEFAULT_CAPACITY);
}

TEST(ByteBufferContruction, INIT_CAPACITY_PROVIDED) {
  norodb::ByteBuffer buff(99);

  ASSERT_EQ(buff.size(), 0);
  ASSERT_EQ(buff.capacity(), 99);

  norodb::ByteBuffer buff2(1);

  ASSERT_EQ(buff2.size(), 0);
  ASSERT_EQ(buff2.capacity(), 1);
}

// Test that ByteBuffer grows as expected
TEST(ByteBufferGrow, NO_PARAMS) {
  norodb::ByteBuffer buff;
  ASSERT_EQ(buff.size(), 0);
  ASSERT_EQ(buff.capacity(), DEFAULT_CAPACITY);
  buff.grow();
  ASSERT_EQ(buff.size(), 0);
  ASSERT_EQ(buff.capacity(), DEFAULT_CAPACITY * 2);
}

// Test that ByteBuffer grows as expected
TEST(ByteBufferGrow, GROW_CAPACITY_PROVIDED) {
  norodb::ByteBuffer buff;
  ASSERT_EQ(buff.size(), 0);
  ASSERT_EQ(buff.capacity(), DEFAULT_CAPACITY);
  buff.grow(1001);
  ASSERT_EQ(buff.size(), 0);
  ASSERT_EQ(buff.capacity(), 1001)
      << "Expected capacity: " << 1257 << ", real: " << buff.capacity();
}

TEST(ByteBufferPut, Put) {
  norodb::ByteBuffer buff;
  buff.put('a');
  ASSERT_EQ(buff.size(), 1);
  ASSERT_EQ(buff.to_string(), "a");
}

// Test that if the capacity is too low to add new elements,
// the buffer will grow
TEST(ByteBufferPut, PutWillGrow) {
  int cap = 1;
  norodb::ByteBuffer buff(cap);

  buff.put(static_cast<uint8_t>('a'));
  ASSERT_EQ(buff.size(), 1);
  ASSERT_EQ(buff.get_wpos(), 1);
  ASSERT_EQ(buff.capacity(), cap);
  ASSERT_EQ(buff.to_string(), "a");

  buff.put(static_cast<uint8_t>('b'));
  ASSERT_EQ(buff.size(), 2)
      << "ByteBuffer::size is " << buff.size() << ", but expected " << 2;
  ASSERT_EQ(buff.capacity(), 2) << "ByteBuffer::capacity is " << buff.capacity()
                                << ", but expected " << 2;
  ASSERT_EQ(buff.to_string(), "ab");
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
