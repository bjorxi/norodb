#ifndef NORO_DB_INDEX_FILE_H_
#define NORO_DB_INDEX_FILE_H_

#include <filesystem>

#include "byte_buffer.h"
#include "db_file.h"
#include "db_directory.h"
#include "db_options.h"

namespace fs = std::filesystem;

namespace norodb {

class IndexFile: public DBFile {
  public:
    IndexFile(uint32_t file_id, DBDirectory& dir, DBOptions& options);
    IndexFile(fs::path fpath, DBDirectory& dir, DBOptions& options);
};

} // namespace norodb

#endif
