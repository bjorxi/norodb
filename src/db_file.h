#ifndef NORO_DB_DB_FILE_H_
#define NORO_DB_DB_FILE_H_

#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>

#include "byte_buffer.h"
#include "db_directory.h"
#include "db_options.h"
#include "row.h"

namespace norodb {

enum FileType { DATA_FILE, INDEX_FILE, COMPACTED_FILE };

class DBFile {
  uint64_t write_offset = 0;
  uint32_t file_id;
  std::fstream file;

  DBDirectory db_dir;
  DBOptions db_options;

 public:
  DBFile(uint32_t file_id, DBDirectory& dir, DBOptions& options);

  /**
   * Writes a ByteByffer object to a file
   *
   * @param buff - a Bytebuffer object
   */
  void write(ByteBuffer& buff);

  /**
   * Writes a row to a file
   *
   * @param row - a porinter to a Row object
   */
  uint64_t write_row(Row& row);

  /**
   * Reads `size` amount of bytes from the `offset` location in a file
   *
   * @param offset - file offset from where reading starts
   * @param size - number of bytes to be read
   *
   * @return a pointer to a ByteBuffer object filled with read data
   */
  ByteBuffer* read(uint64_t offset, uint64_t size);
  void read(uint64_t offset, uint64_t size, ByteBuffer& dest_buff);

  void read(uint64_t offset, ByteBuffer& dest_buff);

  /**
   * Reads from a file at the location `offset` and deserializes read bytes to a
   * Row object
   *
   * @param offset - location from which a read is done
   * @return a pointer to a Row object
   */
  Row* read_row(uint64_t offset);

  /**
   * Forces to write the data that is still in the stream/os buffers to the disk
   */
  void flush() { file.flush(); }

  /**
   * Closes the opened file
   */
  void close();
  void remove();

  uint64_t get_write_offset() { return write_offset; };
};

}  // namespace norodb

#endif
