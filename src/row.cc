#include "row.h"

#include <iostream>
#include <sstream>
#include <string>

#include "third_party/leveldb/coding.h"

namespace norodb {

std::string RowHeader::to_string() {
  std::stringstream s;

  s << "RowHeader(check_sum=" << check_sum << ", version=" << version << ", key_size=" << key_size
    << ", val_size=" << val_size << ", seq_num=" << seq_num << ")";

  return s.str();
}

// Serializes a header to a bytearray so it can be written to a  file
ByteBuffer* RowHeader::serialize() {
  auto buff = new ByteBuffer();
  buff->put_long(check_sum);
  buff->put(version);
  buff->put(key_size);
  buff->put_int(val_size);
  buff->put_long(seq_num);

  return buff;
}

// Recreates a header from a byte array
RowHeader* RowHeader::deserialize(ByteBuffer& buff) {
  return new RowHeader(buff.get_long(), buff.get(), buff.get(), buff.get_int(), buff.get_long());
}

Row::Row(ByteBuffer* key, ByteBuffer* val) {
  this->key = key;
  this->val = val;
  header = new RowHeader(0, 0, key->size(), val->size(), 0);
  _size = key->size() + val->size() + header->size();
}

ByteBuffer* Row::serialize() {
  auto buff = new ByteBuffer();
  buff->put(header->serialize());
  buff->put(key);
  buff->put(val);
  return buff;
}

Row* Row::deserialize(ByteBuffer& buffer, uint8_t key_size, uint32_t val_size) {
  uint8_t key_buff[key_size];
  uint8_t val_buff[val_size];

  buffer.get_bytes(key_buff, key_size);
  buffer.get_bytes(key_buff, key_size);
  auto key = new ByteBuffer(key_buff, key_size);
  auto val = new ByteBuffer(val_buff, val_size);

  return new Row(key, val);
}

Row::~Row() {
  // delete key;
  // delete val;
  // delete header;
}

}  // namespace norodb
