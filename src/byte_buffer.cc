#include <iostream>
#include <sstream>

#include "byte_buffer.h"

namespace norodb {

ByteBuffer::ByteBuffer() {
  buff = std::vector<uint8_t>(DEFAULT_CAPACITY);
}

ByteBuffer::ByteBuffer(uint32_t size) {
  buff = std::vector<uint8_t>(size);
}

ByteBuffer::ByteBuffer(std::string src) {
  buff = std::vector<uint8_t>(DEFAULT_CAPACITY);
  for (auto it = src.cbegin() ; it != src.cend(); ++it) {
    put(*it);
  }
}

std::string ByteBuffer::to_string() {
  std::stringstream s;

  for (int i = 0; i < wpos; i++) {
    s << get(i);
  }

  return s.str();
}

uint8_t ByteBuffer::get() {
  // TODO check if rpos >= size
  uint8_t val = buff[rpos];

  rpos+=1;
  return static_cast<int>(val);
}

uint8_t ByteBuffer::get(uint32_t pos) {
  // TODO check if pos >= size
  uint8_t val = buff[pos];

  return static_cast<int>(val);
}

uint32_t ByteBuffer::get_int() {
  // TODO check if rpos >= size
  uint32_t val = (static_cast<uint32_t>(buff[rpos])) |
                 (static_cast<uint32_t>(buff[rpos+1]) << 8) |
                 (static_cast<uint32_t>(buff[rpos+2]) << 16) |
                 (static_cast<uint32_t>(buff[rpos+3]) << 24);

  rpos += INT_SIZE;

  return val;
}

uint64_t ByteBuffer::get_long() {
  // TODO check if rpos >= size
  uint64_t val = (static_cast<uint64_t>(buff[rpos+0])) |
                 (static_cast<uint64_t>(buff[rpos+1]) << 8) |
                 (static_cast<uint64_t>(buff[rpos+2]) << 16) |
                 (static_cast<uint64_t>(buff[rpos+3]) << 24) |
                 (static_cast<uint64_t>(buff[rpos+4]) << 32) |
                 (static_cast<uint64_t>(buff[rpos+5]) << 40) |
                 (static_cast<uint64_t>(buff[rpos+6]) << 48) |
                 (static_cast<uint64_t>(buff[rpos+7]) << 56);

  rpos += LONG_SIZE;

  return val;
}

void ByteBuffer::put(uint8_t b) {
  if (wpos + 1 > size()) {
    grow();
  }

  buff[wpos] = b;
  wpos += 1;
}

void ByteBuffer::put_int(uint32_t value) {
  if (wpos + INT_SIZE > size()) {
    grow();
  }

  buff[wpos] = static_cast<uint8_t>(value);
  buff[wpos+1] = static_cast<uint8_t>(value >> 8);
  buff[wpos+2] = static_cast<uint8_t>(value >> 16);
  buff[wpos+3] = static_cast<uint8_t>(value >> 24);

  wpos += INT_SIZE;
}

void ByteBuffer::put_long(uint64_t value) {

  if (wpos + LONG_SIZE > size()) {
    grow();
  }

  buff[wpos+0] = static_cast<uint8_t>(value);
  buff[wpos+1] = static_cast<uint8_t>(value >> 8);
  buff[wpos+2] = static_cast<uint8_t>(value >> 16);
  buff[wpos+3] = static_cast<uint8_t>(value >> 24);
  buff[wpos+4] = static_cast<uint8_t>(value >> 32);
  buff[wpos+5] = static_cast<uint8_t>(value >> 40);
  buff[wpos+6] = static_cast<uint8_t>(value >> 48);
  buff[wpos+7] = static_cast<uint8_t>(value >> 56);

  wpos += LONG_SIZE;
}

void ByteBuffer::put(ByteBuffer* src) {
  if (wpos + src->size() > size()) {
    grow(size()*2 + src->size());
  }

  for (int i = 0; i < src->size(); i++) {
    buff[wpos+i] = src->get(i);
  }
}

} // namespace norodb
