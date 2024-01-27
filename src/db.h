#ifndef NORO_DB_DB_H_
#define NORO_DB_DB_H_

#include <atomic>
#include <memory>
#include <mutex>
#include <string>
#include <filesystem>

#include "byte_buffer.h"
#include "db_directory.h"
#include "db_file.h"
#include "db_options.h"
#include "data_file.h"
#include "row.h"
#include "status.h"
#include "index.h"
#include "index_file.h"

namespace fs = std::filesystem;

namespace norodb {

class DB {
  std::string directory;
  DBOptions db_options;
  DBDirectory db_dir;
  DBIndex index;
  std::unique_ptr<DataFile> curr_data_file;  // current data file
  std::mutex write_lock;
  uint64_t seq_num = 0;  // sequence number
  std::atomic<uint32_t> file_id = 0;
  std::unordered_map<std::string, std::unique_ptr<DataFile>> data_files_map;

  /**
   * Goes over existing data files and builds a map of path => DataFile key value pairs.
   *
   * @return max file id found
   */
  uint32_t build_data_files_map();

  /**
   * Builds and index from the index files
   */
  void build_index();

 public:
  DB(const std::string& dir, const DBOptions& opts) : directory(dir), db_options(opts){};
  Status open();

  /**
   * Adds a key/valiue  pair to the db.
   *
   * @param key - a ByteBuffer that represents a key
   * @param val - a ByteBuffer that represents a value
   * @return status of the operation
   */
  Status put(ByteBuffer& key, ByteBuffer& val);

  /**
   * Searches for a key represented by a ByteBuffer. If a value assosiated with the key
   * is found it's returned, otherwise ... #TODO fix this doc
   *
   * @param key - a ByteBuffer that represents a key
   * @param val - a ByteBuffer that will be used to write the foud value.
   */
  Status get(ByteBuffer& key, ByteBuffer& val);
  Status remove(const ByteBuffer& key);

  /**
   * Writes a row to the current data file. If there is no open data file or the
   * current data file file size will exceed the max file size (check DBOptions) then
   * the current data file will be closed and a new data file will be opened
   *
   * @param row - a row to be written
   * @return offset at which a row was written
   */
  uint64_t write_row(Row& row);
  /**
   * Flushes and closes the current data file and cretes a new one
   */
  void roll_over_current_data_file();

  uint32_t get_next_file_id() {
    file_id++;
    return file_id;
  }
};
}  // namespace norodb

#endif
