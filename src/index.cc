#include "index.h"

namespace norodb {

IndexEntry DBIndex::dummy(-1,-1,-1,-1);

void DBIndex::put(ByteBuffer& key, IndexEntry& entry) {
  write_lock.lock();
  IndexEntryHeader ie_header{13, 15, static_cast<uint8_t>(key.size()), 19};
  ByteBuffer buff{IndexEntryHeader::SIZE + key.size() + IndexEntry::SIZE};
  buff.put(ie_header.serialize().get());
  std::cout << "[DBIndex::put] writing size " << buff.size() << std::endl;
  buff.put(&key);
  std::cout << "[DBIndex::put] writing size " << buff.size() << std::endl;
  buff.put(entry.serialize().get());
  std::cout << "[DBIndex::put] writing size " << buff.size() << std::endl;
  std::cout << "[DBIndex::put] header " << ie_header << std::endl;
  std::cout << "[DBIndex::put] entry " << entry << std::endl;

  // key, entry
  write_entry(buff);
  data[key.to_string()] = entry;
  write_lock.unlock();
}

void DBIndex::write_entry(ByteBuffer& buff) {
  if (!curr_index_file or
      curr_index_file->get_write_offset() + buff.size() > db_options.MAX_FILE_SIZE) {
    roll_over_current_index_file();
  }
  std::cout << "[DBIndex::write_entry] " << *curr_index_file << std::endl;
  curr_index_file->write(buff);
}


void DBIndex::roll_over_current_index_file() {
  if (curr_index_file) {
    curr_index_file->flush();
  }

  curr_index_file = std::unique_ptr<IndexFile>(new IndexFile(get_next_file_id(), db_dir, db_options));
}

} // namespace norodb
