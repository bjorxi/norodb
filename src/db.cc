#include <iostream>

#include "db.h"


namespace norodb {

Status DB::open() {
  fs::path p("norodb");
  DBDirectory db_dir(p);
  std::cout << "db dir path " << db_dir.get_path() << std::endl;
  std::cout << "data files path " << db_dir.get_data_dir() << std::endl;
  std::cout << "index files path " << db_dir.get_index_dir() << std::endl;

  return Status(true);
}

Status DB::put(const ByteBuffer& key, const ByteBuffer &val) {
  return Status(true);
}

Status DB::get(const ByteBuffer& key, ByteBuffer& val) {
  return Status(true);
}

Status DB::remove(const ByteBuffer& key) {
  return Status(true);
}

} // namespace norodb
