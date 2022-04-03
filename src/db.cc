#include <iostream>

#include "db.h"


namespace norodb {

Status DB::open() {
  DBDirectory db_dir(directory);
  std::cout << db_dir.get_path() << std::endl;
  std::cout << "data files path " << db_dir.get_data_files_path() << std::endl;
  std::cout << "index files path " << db_dir.get_data_files_path() << std::endl;

  return Status(true);
}

Status DB::put(const ByteArr& key, const ByteArr &val) {
  return Status(true);
}

Status DB::get(const ByteArr& key, ByteArr& val) {
  return Status(true);
}

Status DB::remove(const ByteArr& key) {
  return Status(true);
}

} // namespace norodb
