#ifndef NORO_DB_INDEX_FILE_ENTRY_H_
#define NORO_DB_INDEX_FILE_ENTRY_H_

#include <memory>

#include "byte_buffer.h"
#include "index_entry.h"

namespace norodb {

class IndexFileEntry {
  static const int HEADER_SIZE = 22;
  static const int INDEX_ENTRY_FILE_SIZE = 46;
  static const int CHECKSUM_OFFSET = 0;
  static const int VERSION_OFFSET = 8;
  static const int KEY_SIZE_OFFSET = 9;
  static const int VALUE_SIZE_OFFSET = 10;
  static const int SEQUENCE_NUMBER_OFFSET = 14;
  static const int INDEX_ENTRY_OFFSET = 22;

  uint64_t check_sum;
  uint8_t version;
  uint8_t key_size;
  uint32_t entry_size;
  uint64_t seq_num;
  ByteBuffer key;
  IndexEntry entry;

  public:
    IndexFileEntry(uint64_t check_sum, uint8_t version, uint8_t key_size, uint32_t entry_size,
            uint64_t seq_num)
      : check_sum(check_sum),
        version(version),
        key_size(key_size),
        entry_size(entry_size),
        seq_num(seq_num){};

    IndexFileEntry(ByteBuffer& key, IndexEntry& entry) : key(key), entry(entry) {};

    std::shared_ptr<ByteBuffer> serialize();
    std::shared_ptr<IndexFileEntry> deserialize();

    uint64_t get_check_sum() {return check_sum;}
    uint8_t get_version() {return version;}
    uint8_t get_key_size() {return key_size;}
    uint32_t get_entry_size() {return entry_size;}
};

} // namespace norodb

#endif
