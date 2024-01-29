#include "db_file.h"
#include <cerrno>
#include <cstring>

namespace norodb {
void DBFile::write(ByteBuffer& buff) {
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
  delete[] _buff;
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
  file.seekg(offset);
  file.read(dest_buff.ptr(), dest_buff.size());
}

}  // namespace norodb
