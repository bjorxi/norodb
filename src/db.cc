#include <iostream>

#include "db.h"


namespace norodb {

Status DB::open() {
  return Status(true);
}

Status DB::put(const ByteArr& key, const ByteArr &val) {
  return Status(true);
}

Status DB::get(const ByteArr& key, ByteArr& val) {
  return Status(true);
}

Status DB::remove(const ByteArr& key) {
  return Status(true);
}

}
