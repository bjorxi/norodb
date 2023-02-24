#include "index_entry.h"

namespace norodb {

std::shared_ptr<ByteBuffer> IndexEntry::serialize() {
  std::shared_ptr<ByteBuffer>  buffer(new ByteBuffer());

  buffer->put_int(file_id);
  buffer->put_long(val_offset);
  buffer->put_int(val_size);
  buffer->put_long(seq_num);

  return buffer;
}

std::shared_ptr<IndexEntry> IndexEntry::deserialize(ByteBuffer& buffer) {
  std::shared_ptr<IndexEntry> entry(new IndexEntry(
    buffer.get_int(), buffer.get_long(), buffer.get_int(), buffer.get_long()
  ));

  return entry;
}

} // namespace norodb
