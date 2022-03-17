#ifndef NORO_DB_DB_H_
#define NORO_DB_DB_H_

#include <string>

#include "db_options.h"
#include "byte_arr.h"
#include "status.h"

namespace norodb {

class DB {
  std::string directory;
  DBOptions db_options;


  public:
    DB(const std::string& dir, const DBOptions& opts) : directory(dir), db_options(opts) {}
    Status open();

    Status put(const ByteArr& key, const ByteArr &val);
    Status get(const ByteArr& key, ByteArr& val);
    Status remove(const ByteArr& key);
};
} // namespace norodb

#endif
