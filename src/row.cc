#include <string>

#include "row.h"
#include "third_party/leveldb/coding.h"

namespace norodb {

// Serializes a header to a bytearray so it can be written to a  file
ByteArr* RowHeader::serialize() {
  std::string buff; // we know header size, can create a string of required lenght
  leveldb::PutFixed64(&buff, check_sum);
  leveldb::PutFixed32(&buff, version);
  leveldb::PutFixed32(&buff, key_size);
  leveldb::PutFixed32(&buff, val_size);
  leveldb::PutFixed64(&buff, seq_num);
  leveldb::PutFixed32(&buff, row_size);

  return new ByteArr(buff);
}

// Recreates a header from a byte array
RowHeader* RowHeader::deserialize(const ByteArr& buffer) {
  return new RowHeader(0, 0, 0, 0, 0);
}



Row::Row(const ByteArr* key, const ByteArr* val) {
  this->key = key;
  this->val = val;
  header = new RowHeader(0, 0, 0, 0, 0);
}


Row* Row::deserialize(const ByteArr& buffer) {
  ByteArr* key;
  ByteArr* val;
  return new Row(key, val);
}

Row::~Row() {
  delete key;
  delete val;
  delete header;
}


} // namespace norodb
