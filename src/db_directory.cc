#include "db_directory.h"

#include <iostream>

namespace norodb {

DBDirectory::DBDirectory(const std::string &p) {
  if (p.size() > 0) {
    db_dir = fs::path(p);
  } else {
    db_dir = fs::path("norodb");
  }

  std::cout << "DBDirecotry::data_files_dir: " << data_files_dir << std::endl;
  data_files_dir = db_dir / "data";
  std::cout << "DBDirecotry::data_files_dir: " << data_files_dir << std::endl;
  index_files_dir = db_dir / "index";
}

DBDirectory::DBDirectory(fs::path dir) {
  db_dir = dir;
  data_files_dir = dir / "data";

  std::cout << "DBDirecotry::data_files_dir: " << data_files_dir << std::endl;

  index_files_dir = dir / "index";

  std::cout << "DBDirecotry::index_files_dir: " << index_files_dir << std::endl;
}

DBDirectory *DBDirectory::open(fs::path dir) { return new DBDirectory(dir); }

} // namespace norodb
