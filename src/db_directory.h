#ifndef NORO_DB_DB_DIRECTORY_H_
#define NORO_DB_DB_DIRECTORY_H_

#include <filesystem>
#include <string>
#include <vector>

#include "status.h"

namespace fs = std::filesystem;

namespace norodb {

class DBDirectory {
  fs::path db_dir;
  fs::path data_files_dir;
  fs::path index_files_dir;

public:
  DBDirectory(const std::string &p);
  DBDirectory() { db_dir = "norodb"; };
  DBDirectory(fs::path dir);
  static DBDirectory *open(fs::path dir);
  void close();
  void create_directories();
  fs::path get_path() { return db_dir; };
  fs::path get_data_dir() { return data_files_dir; };
  fs::path get_index_dir() { return index_files_dir; };
  std::vector<fs::path> list_data_files();
  std::vector<fs::path> list_index_files();
};

} // namespace norodb

#endif
