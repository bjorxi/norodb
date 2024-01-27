#include "db.h"

#include <iostream>

#include "constants.h"

namespace norodb {

// build a dict {filename => fileobj} and open those files; and find and set max_file_id
// load metadata from a metadafile
// build index
// start the compaction process
// start the compaction process for tombsones
Status DB::open() {
  fs::path p("norodb");
  db_dir = DBDirectory(p);

  file_id = build_data_files_map();
  std::cout << "DB::open file_id " << file_id << std::endl;

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

  if (index_entry.get_file_id() == -1) {
    return Status(false);
  }

  auto row = curr_data_file->read_row(index_entry.get_val_offset());
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

  curr_data_file = std::unique_ptr<DataFile>(new DataFile(get_next_file_id(), db_dir, db_options));
}


uint32_t DB::build_data_files_map() {
  uint32_t max_file_id = 0;
  auto data_files = db_dir.list_data_files();

  for (auto it = begin(data_files); it != end(data_files); ++it) {
    auto file_name = it->filename().string();
    auto file_id_str = file_name.replace(1, file_name.length()-1, "");
    auto file_id = static_cast<uint32_t>(std::stoi(file_id_str));

    max_file_id = std::max(file_id, max_file_id);

    data_files_map[file_name] = std::unique_ptr<DataFile>(new DataFile{file_id, db_dir, db_options});
  }

  return max_file_id;
}

void DB::build_index() {
  auto index_files = db_dir.list_index_files();

  std::cout << "DB::open: " << index_files.size() << " index_files found " <<  std::endl;
  for (auto it = begin(index_files); it != end(index_files); ++it) {
    std::cout << "DB::open::index_files: " << *it << std::endl;
    IndexFile _if{fs::path(*it), db_dir, db_options};
    ByteBuffer bb;

    _if.read(0, IndexFileEntry::HEADER_SIZE, bb);
    std::cout << "header: " << bb.to_string() << std::endl;
  }
}

}  // namespace norodb
