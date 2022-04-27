#include "db_directory.h"

#include <iostream>

namespace norodb {

DBDirectory::DBDirectory(const std::string& p) {
  if (p.size() > 0) {
    db_dir = fs::path(p);
  } else {
    db_dir = fs::path("norodb");
  }

  data_files_dir = db_dir / "data";
  index_files_dir = db_dir / "index";
  create_directories();
}

DBDirectory::DBDirectory(fs::path dir) {
  db_dir = dir;
  data_files_dir = dir / "data";
  index_files_dir = dir / "index";
  create_directories();
}

DBDirectory* DBDirectory::open(fs::path dir) { return new DBDirectory(dir); }

// Creates dirctories used by the DB.
void DBDirectory::create_directories() {
  if (!fs::exists(db_dir)) fs::create_directory(db_dir);

  if (!fs::exists(data_files_dir)) fs::create_directory(data_files_dir);

  if (!fs::exists(index_files_dir)) fs::create_directory(index_files_dir);
}

}  // namespace norodb
