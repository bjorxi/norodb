#ifndef NORO_DB_INDEX_H_
#define NORO_DB_INDEX_H_

#include <unordered_map>
#include <string>
#include <memory>
#include <mutex>
#include <atomic>

#include "byte_buffer.h"
#include "index_file.h"
#include "db_directory.h"
#include "db_options.h"
#include "index_entry.h"
#include "index_file_entry.h"

namespace norodb {

class DBIndex {
  DBOptions db_options;
  DBDirectory db_dir;
  std::unordered_map<std::string, IndexEntry> data; // in-memory index
  std::unique_ptr<IndexFile> curr_index_file;
  std::atomic<uint32_t> file_id = 0;
  std::mutex write_lock;
  std::atomic<uint64_t> index_entry_id = 0;

  public:
    static IndexEntry dummy;

    void put(ByteBuffer& key, IndexEntry& entry);

    IndexEntry get(ByteBuffer& key) {
      auto _key = key.to_string();
      if (data.find(_key) != data.end()) {
        return data[_key];
      }

      return dummy;
    }

    void remove(ByteBuffer& key);
    void write_entry(ByteBuffer& buff);
    void roll_over_current_index_file();

    uint32_t get_next_file_id() {
      file_id++;
      return file_id;
    }

    uint64_t get_next_index_entry_id() {
      index_entry_id += 1;
      return index_entry_id;
    }
};

}  // namespace norodb

#endif
