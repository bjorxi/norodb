#ifndef NORO_DB_INDEX_ENTRY_H_
#define NORO_DB_INDEX_ENTRY_H_

#include <iostream>
#include <memory>
#include <tuple>

#include "byte_buffer.h"

namespace norodb {


class IndexEntryHeader {
  static const int CHECKSUM_OFFSET = 0;
  static const int VERSION_OFFSET = 8;
  static const int KEY_SIZE_OFFSET = 9;
  static const int VALUE_SIZE_OFFSET = 10;
  static const int SEQUENCE_NUMBER_OFFSET = 14;
  static const int INDEX_ENTRY_OFFSET = 22;

  uint64_t check_sum;
  uint8_t version;
  uint8_t key_size;
  uint64_t seq_num;
public:
  static const int SIZE = 18;

  IndexEntryHeader() {};
  IndexEntryHeader(uint64_t check_sum, uint8_t version, uint8_t key_size, uint64_t seq_num)
      : check_sum(check_sum),
        version(version),
        key_size(key_size),
        seq_num(seq_num)
        {};

  std::shared_ptr<ByteBuffer> serialize();
  static std::shared_ptr<IndexEntryHeader> deserialize(ByteBuffer& buff);

  uint64_t get_check_sum() { return check_sum; }
  uint8_t get_version() { return version; }
  uint8_t get_key_size() { return key_size; }
  uint64_t get_seq_num() {return seq_num; }

  // for debugging
  friend std::ostream& operator<<(std::ostream& os, const IndexEntryHeader& header) {
    os << "IndexEntryHeader(check_sum=" << header.check_sum << "; " <<
   "key_size=" << std::to_string(header.key_size) << "; " <<
   "version=" << std::to_string(header.version) << "; " <<
   "seq_num=" << header.seq_num << ")";

   return os;
  }
};


class IndexEntry {
  uint32_t file_id = 101;
  uint64_t val_offset = 0;
  uint32_t val_size = 0;
  uint64_t seq_num = 3;

  public:
    static const uint32_t SIZE = 24; // bytes

    IndexEntry() {};
    IndexEntry(uint32_t file_id, uint64_t val_offset,  uint32_t val_size, uint64_t seq_num) :
      file_id(file_id), val_offset(val_offset), val_size(val_size), seq_num(seq_num) {};

    uint32_t get_file_id() {return file_id;}
    uint64_t get_val_offset() {return val_offset;}
    uint32_t get_val_size() {return val_size;}
    uint64_t get_seq_num() {return seq_num;}

    void set_file_id(uint32_t fid) {file_id = fid;}
    void set_val_offset(uint64_t offset) {val_offset = offset;}
    void set_val_size(uint32_t size) {val_size = size;}
    void set_seq_num(uint32_t num) {seq_num = num;}

    std::shared_ptr<ByteBuffer> serialize();
    static std::shared_ptr<IndexEntry> deserialize(ByteBuffer& buffer);

    friend std::ostream& operator<<(std::ostream& os, const IndexEntry& entry) {
      os << "IndexEntry(file_id=" << entry.file_id << "; " <<
     "val_offset=" << std::to_string(entry.val_offset) << "; " <<
     "val_size=" << std::to_string(entry.val_size) << "; " <<
     "seq_num=" << entry.seq_num << ")";

     return os;
    }
};
} // namespace norodb

#endif
