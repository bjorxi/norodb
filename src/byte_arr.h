#ifndef NORO_DB_BYTE_ARR_H_
#define NORO_DB_BYTE_ARR_H_

#include <stddef.h>
#include <string>


namespace norodb {

class ByteArr {
  const char* _data;
  size_t _size;

  public:
    ByteArr() : _data(""), _size(0) {}
    ByteArr(const char* d, size_t n) : _data(d), _size(n) {}
    ByteArr(const std::string& s) : _data(s.data()), _size(s.size()) {}

    const char* data() const {
      return _data;
    }

    size_t size() const {
      return _size;
    }
};
} // namespace norodb

#endif
