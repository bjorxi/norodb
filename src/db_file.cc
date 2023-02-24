#include "db_file.h"
#include <cerrno>
#include <cstring>

namespace norodb {
//
// DBFile::DBFile(uint32_t file_id, DBDirectory& dir, DBOptions& options)
//     : file_id(file_id), db_dir(dir), db_options(options) {
//   std::stringstream fname;
//   fname << file_id << ".data";
//
//   fs::path data_file_path = db_dir.get_data_dir() / fname.str();
//   std::cout << "Opening a file, path: " << data_file_path << std::endl;
//   file.open(data_file_path.string(),
//             std::ios::in | std::ios::out | std::ios::app | std::ios::ate | std::ios::binary);
// }

void DBFile::write(ByteBuffer& buff) {
  int written;

  // std::cout << "Writing a buffer: " <<  buff.to_string() << std::endl;
  file.write(buff.ptr(), buff.size());


  if (db_options.FLUSH_ON_WRITE) {
    file.flush();
  }

  if (!file) {
    std::cout << "Failed to write a buffer: " << std::strerror(errno) << std::endl;
  }
}

ByteBuffer* DBFile::read(uint64_t offset, uint64_t size) {
  char* _buff = new char[size];
  file.seekg(offset);
  file.read(_buff, size);
  auto buff = new ByteBuffer(_buff);
  delete _buff;
  return buff;
}

void DBFile::read(uint64_t offset, uint64_t size, ByteBuffer& dest_buff) {
  char* _buff = new char[size];
  file.seekg(offset);
  file.read(_buff, size);
  uint8_t* _ptr = reinterpret_cast<uint8_t*>(_buff);
  dest_buff.put_bytes(_ptr, size);
}

void DBFile::read(uint64_t offset, ByteBuffer& dest_buff) {
  // char* _buff = new char[dest_buff.size()];
  file.seekg(offset);
  file.read(dest_buff.ptr(), dest_buff.size());
}

}  // namespace norodb
