#include <iostream>

#include "db_file.h"

namespace norodb {
DBFile::DBFile(uint32_t file_id, const DBDirectory &db_dir) {
  this->file_id = file_id;
  this->db_dir = db_dir;
  std::stringstream fname;
  fname << file_id << ".data";

  file.open(fname.str(),
            std::ios::in | std::ios::out | std::ios::app | std::ios::binary);
}

void DBFile::write(ByteBuffer &buff) {
  std::cout << "DBFile::write | writing a buffer of size:" << buff.size()
            << std::endl;
  file.write(buff.to_string().c_str(), buff.size());
  std::cout << "DBFile::write | done writing a buffer of size:" << buff.size()
            << std::endl;
  write_offset += buff.size();
}

} // namespace norodb
