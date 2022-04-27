#include <iostream>

#include "db.h"

namespace norodb {

Status DB::open() {
  fs::path p("norodb");
  auto db_dir = new DBDirectory(p);
  data_file = new DBFile(0, db_dir);
  return Status(true);
}

Status DB::put(ByteBuffer &key, ByteBuffer &val) {
  Row row(&key, &val);
  data_file->write(*row.serialize());

  return Status(true);
}

Status DB::get(const ByteBuffer &key, ByteBuffer &val) { return Status(true); }

Status DB::remove(const ByteBuffer &key) { return Status(true); }

} // namespace norodb
