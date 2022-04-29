#ifndef NORO_DB_DB_OPTIONS_H_
#define NORO_DB_DB_OPTIONS_H_

namespace norodb {

class DBOptions {
 public:
  int maxFileSize = 1024 * 1024 * 1024;  // 1GB
  long flushDataSizeBytes = -1;
  bool flush_on_write = true;
};

}  // namespace norodb

#endif
