#include "db.h"

#include <iostream>

#include "constants.h"

namespace norodb {

Status DB::open() {
  fs::path p("norodb");
  db_dir = DBDirectory(p);
  return Status(true);
}

Status DB::put(ByteBuffer& key, ByteBuffer& val) {
  write_lock.lock();
  seq_num++;
  Row row(key, val);
  row.set_seq_num(seq_num);
  row.set_version(DATA_FILE_VERSION);
  uint64_t row_offset = write_row(row);

  IndexEntry entry(file_id, row_offset, val.size(), seq_num);
  index.put(key, entry);

  write_lock.unlock();
  return Status(true);
}

Status DB::get(ByteBuffer& key) {
  auto index_entry = index.get(key);
  auto row = curr_data_file->read_row(index_entry.get_val_offset());

  return Status(true);
}

Status DB::remove(const ByteBuffer& key) { return Status(true); }

uint64_t DB::write_row(Row& row) {
  if (!curr_data_file or
      curr_data_file->get_write_offset() + row.size() > db_options.MAX_FILE_SIZE) {
    roll_over_current_data_file();
  }

  return curr_data_file->write_row(row);
}

void DB::roll_over_current_data_file() {
  if (curr_data_file) {
    curr_data_file->flush();
  }

  curr_data_file = std::unique_ptr<DataFile>(new DataFile(get_next_file_id(), db_dir, db_options));
}

}  // namespace norodb
