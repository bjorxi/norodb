#include "index_entry.h"

namespace norodb {


std::shared_ptr<ByteBuffer> IndexEntryHeader::serialize() {
  std::shared_ptr<ByteBuffer> buff(new ByteBuffer());

  buff->put_long(check_sum);
  buff->put(version);
  buff->put(key_size);
  buff->put_long(seq_num);

  return buff;
}

// Recreates a header from a byte array
std::shared_ptr<IndexEntryHeader> IndexEntryHeader::deserialize(ByteBuffer& buff) {
  return std::shared_ptr<IndexEntryHeader>(
    new IndexEntryHeader(buff.get_long(), buff.get(), buff.get(), buff.get_long())
  );
}


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
