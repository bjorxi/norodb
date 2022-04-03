#ifndef NORO_DB_ROW_H_
#define NORO_DB_ROW_H_

#include <stddef.h>

#include "byte_arr.h"


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
  static const int VERSION_OFFSET = 4;
  static const int KEY_SIZE_OFFSET = 5;
  static const int VALUE_SIZE_OFFSET = 6;
  static const int SEQUENCE_NUMBER_OFFSET = 10;

  static const int HEADER_SIZE = 18;
  static const int CHECKSUM_SIZE = 4;

  long check_sum;
  int version;
  int key_size;
  int val_size;
  long seq_num;
  int row_size;

  public:
    RowHeader(long check_sum, int version, int key_size, int val_size, long seq_num) :
      check_sum(check_sum), version(version), key_size(key_size), val_size(val_size),
      seq_num(seq_num) {};

    ByteArr* serialize();
    static RowHeader* deserialize(const ByteArr& buffer);
};


class Row {
  const ByteArr* key;
  const ByteArr* val;
  RowHeader* header;

  public:
    Row(const ByteArr* key, const ByteArr* val);
    ~Row();

    ByteArr* serialize();
    static Row* deserialize(const ByteArr& buffer);
};

} // namespace norodb
#endif
