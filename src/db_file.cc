#include "db_file.h"

#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

namespace norodb {

DBFile::DBFile(uint32_t file_id, DBDirectory& dir, DBOptions& options)
    : file_id(file_id), db_dir(dir), db_options(options) {
  std::stringstream fname;
  fname << file_id << ".data";

  fs::path data_file_path = db_dir.get_data_dir() / fname.str();

  file.open(data_file_path.string(),
            std::ios::in | std::ios::out | std::ios::app | std::ios::ate | std::ios::binary);
}

void DBFile::write(ByteBuffer& buff) {
  int written;
  file.write(buff.ptr(), buff.size());

  if (db_options.FLUSH_ON_WRITE) {
    file.flush();
  }

  if (!file) {
    std::cout << "Failed to  write a buffer" << std::endl;
  }
}

void DBFile::write_row(Row& row) {
  write(*(row.serialize()));
  uint32_t row_size = row.size();
  uint64_t rowOffSet = write_offset;  // save curr offset to have it in the index entry
  write_offset += row_size;
  // add an index entry
}

ByteBuffer* DBFile::read(uint64_t offset, uint64_t size) {
  char* _buff = new char[size];
  file.seekg(offset);
  file.read(_buff, size);
  auto buff = new ByteBuffer(_buff);
  delete _buff;
  return buff;
}

}  // namespace norodb
