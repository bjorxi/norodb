#ifndef NORO_DB_DB_DIRECTORY_H_
#define NORO_DB_DB_DIRECTORY_H_

#include <filesystem>
#include <string>

#include "status.h"

namespace fs = std::filesystem;

namespace norodb {

class DBDirectory {
  fs::path path;
  fs::path data_files_path;
  fs::path index_files_path;

  public:
    DBDirectory(const std::string& p);
    DBDirectory() {path = "norodb";};
    Status open();
    fs::path get_path() {return path;};
    fs::path get_data_files_path() {return data_files_path;};
    fs::path get_index_files_path() {return index_files_path;};
};



} // namespace norodb

#endif
