#ifndef NORO_DB_DB_H_
#define NORO_DB_DB_H_

#include <string>

#include "db_options.h"
#include "byte_buffer.h"
#include "status.h"
#include "db_directory.h"
#include "row.h"

namespace norodb {

class DB {
  std::string directory;
  DBOptions db_options;

  public:
    DB(const std::string& dir, const DBOptions& opts) : directory(dir), db_options(opts) {}
    Status open();

    Status put(const ByteBuffer& key, const ByteBuffer &val);
    Status get(const ByteBuffer& key, ByteBuffer& val);
    Status remove(const ByteBuffer& key);
};
} // namespace norodb

#endif
