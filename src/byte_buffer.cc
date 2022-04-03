#include "byte_buffer.h"
#include <iostream>

namespace norodb {

ByteBuffer::ByteBuffer() {
  buff = std::vector<uint8_t>(DEFAULT_CAPACITY);
}


ByteBuffer::ByteBuffer(uint32_t size) {
  buff = std::vector<uint8_t>(size);
}


uint32_t ByteBuffer::getInt() {
  uint32_t val = (static_cast<uint32_t>(buff[rpos])) |
                 (static_cast<uint32_t>(buff[rpos+1]) << 8) |
                 (static_cast<uint32_t>(buff[rpos+2]) << 16) |
                 (static_cast<uint32_t>(buff[rpos+3]) << 24);

  rpos += INT_SIZE;

  return val;
}

uint64_t ByteBuffer::getLong() {
  uint64_t val = (static_cast<uint64_t>(buff[rpos+0])) |
                 (static_cast<uint64_t>(buff[rpos+1]) << 8) |
                 (static_cast<uint64_t>(buff[rpos+2]) << 16) |
                 (static_cast<uint64_t>(buff[rpos+3]) << 24) |
                 (static_cast<uint64_t>(buff[rpos+4]) << 32) |
                 (static_cast<uint64_t>(buff[rpos+5]) << 40) |
                 (static_cast<uint64_t>(buff[rpos+6]) << 48) |
                 (static_cast<uint64_t>(buff[rpos+7]) << 56);

  wpos += LONG_SIZE;

  return val;
}

void ByteBuffer::putInt(uint32_t value) {
  if (wpos + INT_SIZE > size()) {
    grow();
  }

  buff[wpos] = static_cast<uint8_t>(value);
  buff[wpos+1] = static_cast<uint8_t>(value >> 8);
  buff[wpos+2] = static_cast<uint8_t>(value >> 16);
  buff[wpos+3] = static_cast<uint8_t>(value >> 24);

  wpos += INT_SIZE;
}

void ByteBuffer::putLong(uint64_t value) {
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

} // namespace norodb
