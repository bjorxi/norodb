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
  Row row(&key, &val);
  row.set_seq_num(seq_num);
  row.set_version(DATA_FILE_VERSION);
  write_row(row);
  // add row to the index
  write_lock.unlock();
  return Status(true);
}

Status DB::get(const ByteBuffer& key) { return Status(true); }

Status DB::remove(const ByteBuffer& key) { return Status(true); }

void DB::write_row(Row& row) {
  if (!curr_data_file or
      curr_data_file->get_write_offset() + row.size() > db_options.MAX_FILE_SIZE) {
    roll_over_current_data_file();
  }

  curr_data_file->write_row(row);
}

void DB::roll_over_current_data_file() {
  if (curr_data_file) {
    curr_data_file->flush();
  }

  curr_data_file = std::unique_ptr<DBFile>(new DBFile(get_next_file_id(), db_dir, db_options));
}

}  // namespace norodb
