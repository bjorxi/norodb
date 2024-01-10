#include "index.h"

namespace norodb {

IndexEntry DBIndex::dummy(-1,-1,-1,-1);

void DBIndex::put(ByteBuffer& key, IndexEntry& entry) {
  write_lock.lock();
  IndexFileEntry ife(key, entry);
  write_entry(*ife.serialize());
  data[key.to_string()] = entry;
  write_lock.unlock();
}

void DBIndex::write_entry(ByteBuffer& buff) {
  if (!curr_index_file or
      curr_index_file->get_write_offset() + buff.size() > db_options.MAX_FILE_SIZE) {
    roll_over_current_index_file();
  }

  curr_index_file->write(buff);
}

void DBIndex::roll_over_current_index_file() {
  if (curr_index_file) {
    curr_index_file->flush();
  }

  curr_index_file = std::unique_ptr<IndexFile>(new IndexFile(get_next_file_id(), db_dir, db_options));
}

} // namespace norodb
