#ifndef NORO_DB_ROW_H_
#define NORO_DB_ROW_H_

#include <stddef.h>

#include <cstdint>

#include "byte_buffer.h"

namespace norodb {

class RowHeader {
  /**
   * crc              - 4 bytes.
   * version          - 1 byte.
   * key size         - 1 bytes.
   * value size       - 4 bytes.
   * sequence number  - 8 bytes.
   */
  static const int CHECKSUM_OFFSET = 0;
  static const int VERSION_OFFSET = 8;
  static const int KEY_SIZE_OFFSET = 9;
  static const int VALUE_SIZE_OFFSET = 10;
  static const int SEQUENCE_NUMBER_OFFSET = 14;

  static const int HEADER_SIZE = 18;
  static const int CHECKSUM_SIZE = 4;

  uint64_t check_sum;
  uint8_t version;
  uint8_t key_size;
  uint32_t val_size;
  uint64_t seq_num;

 public:
  RowHeader(uint64_t check_sum, uint8_t version, uint8_t key_size,
            uint32_t val_size, uint64_t seq_num)
      : check_sum(check_sum),
        version(version),
        key_size(key_size),
        val_size(val_size),
        seq_num(seq_num){};
  ByteBuffer *serialize();
  static RowHeader *deserialize(ByteBuffer &buffer);
  std::string to_string();
  uint32_t size() { return HEADER_SIZE; };
};

class Row {
  ByteBuffer *key;
  ByteBuffer *val;
  RowHeader *header;
  uint32_t _size;

 public:
  Row(ByteBuffer *key, ByteBuffer *val);
  ~Row();

  ByteBuffer *serialize();
  static Row *deserialize(ByteBuffer &buffer);
  uint32_t size() { return _size; };
};

}  // namespace norodb
#endif
