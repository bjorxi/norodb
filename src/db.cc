#include "db.h"

#include <iostream>

namespace norodb {

Status DB::open() {
  fs::path p("norodb");
  auto db_dir = new DBDirectory(p);
  data_file = new DBFile(0, db_dir);
  return Status(true);
}

Status DB::put(ByteBuffer& key, ByteBuffer& val) {
  write_lock.lock();
  Row row(&key, &val);
  data_file->write_row(row);
  write_lock.unlock();
  return Status(true);
}

Status DB::get(const ByteBuffer& key, ByteBuffer& val) { return Status(true); }

Status DB::remove(const ByteBuffer& key) { return Status(true); }

}  // namespace norodb
