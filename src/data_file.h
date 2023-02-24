#ifndef NORO_DB_DATA_FILE_H_
#define NORO_DB_DATA_FILE_H_

#include "byte_buffer.h"
#include "db_file.h"
#include "db_directory.h"
#include "db_options.h"
#include "row.h"

namespace norodb {

class DataFile: public DBFile {
  public:
    DataFile(uint32_t file_id, DBDirectory& dir, DBOptions& options);

    /**
     * Writes a row to a file
     *
     * @param row - a porinter to a Row object
     */
    uint64_t write_row(Row& row);

    /**
     * Reads from a file at the location `offset` and deserializes read bytes to a
     * Row object
     *
     * @param offset - location from which a read is done
     * @return a pointer to a Row object
     */
    Row* read_row(uint64_t offset);
};

} // namespace norodb

#endif
