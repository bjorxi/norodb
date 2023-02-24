#ifndef NORO_DB_INDEX_ENTRY_H_
#define NORO_DB_INDEX_ENTRY_H_

#include <memory>

#include "byte_buffer.h"

namespace norodb {

class IndexEntry {
  uint32_t file_id = 0;
  uint64_t val_offset = 0;
  uint32_t val_size = 0;
  uint64_t seq_num = 0;

  public:
    static const uint32_t SIZE = 24; // bytes

    IndexEntry() {};
    IndexEntry(uint32_t file_id, uint64_t val_offset,  uint32_t val_size, uint64_t seq_num) :
      file_id(file_id), val_offset(val_offset), val_size(val_size), seq_num(seq_num) {};

    uint32_t get_file_id() {return file_id;}
    uint64_t get_val_offset() {return val_offset;}
    uint32_t get_val_size() {return val_size;}
    uint64_t get_seq_num() {return seq_num;}

    std::shared_ptr<ByteBuffer> serialize();
    static std::shared_ptr<IndexEntry> deserialize(ByteBuffer& buffer);
};

} // namespace norodb

#endif
