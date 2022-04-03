#include "db_directory.h"

#include <iostream>

namespace norodb {

DBDirectory::DBDirectory(const std::string& p) {
  if (p.size() > 0) {
    path = p;
  } else {
    path = "norodb";
  }
}

Status DBDirectory::open() {
  data_files_path = path / "data";
  std::cout << path / "data" << std::endl;
  index_files_path = path / "index";
  return Status(true);
}
} // namespace norodb
