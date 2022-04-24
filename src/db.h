#ifndef NORO_DB_DB_H_
#define NORO_DB_DB_H_

#include <string>

#include "byte_buffer.h"
#include "db_directory.h"
#include "db_file.h"
#include "db_options.h"
#include "row.h"
#include "status.h"

namespace norodb {

class DB {
  std::string directory;
  DBOptions db_options;
  DBFile *data_file;

public:
  DB(const std::string &dir, const DBOptions &opts)
      : directory(dir), db_options(opts) {}
  Status open();

  Status put(ByteBuffer &key, ByteBuffer &val);
  Status get(const ByteBuffer &key, ByteBuffer &val);
  Status remove(const ByteBuffer &key);
};
} // namespace norodb

#endif
