#ifndef NORO_DB_STATTUS_H_
#define NORO_DB_STATTUS_H_

namespace norodb {

class Status {
  bool _ok;

 public:
  Status(bool ok) { _ok = ok; }

  bool ok() const { return _ok; }
};
}  // namespace norodb

#endif
