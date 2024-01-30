#include "db.h"

#include <iostream>

#include "constants.h"

namespace norodb {


// build index

// The following actions will be added later
// load metadata from a metadafile
// start the compaction process
// start the compaction process for tombsones
Status DB::open() {
  fs::path p("norodb");
  db_dir = DBDirectory(p);

  build_data_files_map();
  build_index();

  return Status(true);
}

Status DB::put(ByteBuffer& key, ByteBuffer& val) {
  write_lock.lock();
  seq_num++;
  Row row(key, val);
  row.set_seq_num(seq_num);
  row.set_version(DATA_FILE_VERSION);
  uint64_t row_offset = write_row(row);

  IndexEntry entry(file_id, row_offset, val.size(), seq_num);
  index.put(key, entry);

  write_lock.unlock();
  return Status(true);
}

Status DB::get(ByteBuffer& key, ByteBuffer& val) {
  auto index_entry = index.get(key);
  auto data_file_id = index_entry.get_file_id();
  if (data_file_id == -1) { // file_id is unsigned can't be -1 =/
    return Status(false);
  }

  // data_files_map[file_name]
  auto row = data_files_map[data_file_id]->read_row(index_entry.get_val_offset());
  auto _val = row->get_val();
  val.put(&_val);
  return Status(true);
}

Status DB::remove(const ByteBuffer& key) { return Status(true); }

uint64_t DB::write_row(Row& row) {
  if (!curr_data_file or
      curr_data_file->get_write_offset() + row.size() > db_options.MAX_FILE_SIZE) {
    roll_over_current_data_file();
  }

  return curr_data_file->write_row(row);
}

void DB::roll_over_current_data_file() {
  if (curr_data_file) {
    curr_data_file->flush();
  }

  auto next_file_id = get_next_file_id();
  curr_data_file = std::shared_ptr<DataFile>(new DataFile(next_file_id, db_dir, db_options));
  data_files_map[next_file_id] = curr_data_file;
}

void DB::build_data_files_map() {
  uint32_t max_file_id = 0;
  auto data_files = db_dir.list_data_files();

  for (auto it = begin(data_files); it != end(data_files); ++it) {
    auto file_name = it->filename().string();
    auto file_id_str = file_name.replace(1, file_name.length()-1, "");
    auto file_id = static_cast<uint32_t>(std::stoi(file_id_str));
    data_files_map[file_id] = std::shared_ptr<DataFile>(new DataFile{file_id, db_dir, db_options});

    if (file_id > max_file_id) {
      max_file_id = file_id;
    }
  }

  // file_ids start with 1
  if (max_file_id > 0) {
    file_id = max_file_id;
    curr_data_file = data_files_map[file_id];
  }
}

void DB::build_index() {
  auto index_files = db_dir.list_index_files();

  for (auto it = begin(index_files); it != end(index_files); ++it) {
    uint64_t read_offset = 0;
    IndexFile _if{fs::path(*it), db_dir, db_options};
    while (read_offset < _if.write_offset) {
      auto [key_ptr, entry_ptr] = _if.read_entry(read_offset);

      read_offset += IndexEntryHeader::SIZE + key_ptr->size() + IndexEntry::SIZE;
      index.put(*key_ptr, *entry_ptr);
    }
  }
}

}  // namespace norodb
