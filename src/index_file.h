#ifndef NORO_DB_INDEX_FILE_H_
#define NORO_DB_INDEX_FILE_H_

#include <filesystem>
#include <tuple>

#include "byte_buffer.h"
#include "db_file.h"
#include "db_directory.h"
#include "db_options.h"
#include "index_entry.h"

namespace fs = std::filesystem;

namespace norodb {

class IndexFile: public DBFile {
  public:
    IndexFile(uint32_t file_id, DBDirectory& dir, DBOptions& options);
    IndexFile(fs::path fpath, DBDirectory& dir, DBOptions& options);

    std::tuple<std::shared_ptr<ByteBuffer>, std::shared_ptr<IndexEntry>> read_entry(uint64_t offset);
    void read_entry(uint64_t offset, ByteBuffer& key, IndexEntry& entry);
};

} // namespace norodb

#endif
