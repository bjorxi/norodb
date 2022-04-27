#include <iostream>
#include <filesystem>

#include "db_file.h"

namespace fs = std::filesystem;

namespace norodb {

DBFile::DBFile(uint32_t file_id, DBDirectory *db_dir) {
  this->file_id = file_id;
  this->db_dir = db_dir;
  std::stringstream fname;
  fname << file_id << ".data";

  fs::path data_file_path = db_dir->get_data_dir() / fname.str();

  file.open(data_file_path.string(),
            std::ios::in | std::ios::out | std::ios::app | std::ios::binary);
}

void DBFile::write(ByteBuffer &buff) {
  std::cout << "DBFile::write | writing a buffer of size: " << buff.size() << " Str: " << buff.to_string()
            << std::endl;
  file.write(buff.ptr(), buff.size());
  file.flush();
  std::cout << "DBFile::write | done writing a buffer of size:" << buff.size()
            << std::endl;
  write_offset += buff.size();
}

} // namespace norodb
