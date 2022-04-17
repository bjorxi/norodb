#ifndef NORO_DB_DB_FILE_H_
#define NORO_DB_DB_FILE_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdint>

#include "byte_buffer.h"
#include "db_directory.h"

namespace norodb {

enum FileType {DATA_FILE, INDEX_FILE, COMPACTED_FILE};


class DBFile {
  uint64_t write_offset = 0;
  uint32_t file_id;
  DBDirectory db_dir;
  std::fstream file;

  public:
    DBFile(uint32_t file_id, const DBDirectory& db_dir);
    void write(ByteBuffer& buff);
    ByteBuffer* read();
    ByteBuffer* read(uint64_t offset);
    void close();
    void remove();
};

} // namespace norodb

#endif
