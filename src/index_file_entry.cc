#include "index_file_entry.h"


namespace norodb {


std::shared_ptr<ByteBuffer> IndexFileEntry::serialize() {
  std::shared_ptr<ByteBuffer> buff(new ByteBuffer());

  auto index_entry_buffer = entry.serialize();
  buff->put_long(check_sum);
  buff->put(version);
  buff->put(key.size());
  buff->put_int(index_entry_buffer->size());
  buff->put_long(seq_num);
  buff->put(&key);
  buff->put(index_entry_buffer.get());

  return buff;
}

} // namespace norodb
