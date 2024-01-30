#ifndef NORO_DB_DB_OPTIONS_H_
#define NORO_DB_DB_OPTIONS_H_

namespace norodb {

class DBOptions {
 public:
  /**
   * 1GB. If current DBFile exceeds this limit a new DBFile will be created
   */
  uint32_t MAX_FILE_SIZE = 1024 * 1024 * 1024;

  /**
   * If is positive buffers will be flushed to the disk once the buffer size grows bigger
   * than this value
   */
  uint32_t FLUSH_DATA_SIZE_BYTES = -1;

  bool FLUSH_ON_WRITE = true;  // if true, buffers will flushed to the disl after every write
};

}  // namespace norodb

#endif
