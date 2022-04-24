#include <filesystem>
#include <iostream>

#include "byte_buffer.h"
#include "db.h"
#include "row.h"

namespace fs = std::filesystem;

int main() {
  norodb::DBOptions opts;
  norodb::DB db("", opts);
  db.open();
  norodb::ByteBuffer key("key");
  norodb::ByteBuffer val("val");

  db.put(key, val);

  //
  // norodb::ByteArr key;
  // norodb::ByteArr val;
  //
  // db.put(key, val);

  // norodb::RowHeader rh(1,2,3,4,5);
  //   std::cout << rh.to_string() << std::endl;
  //
  // auto buffer = rh.serialize();
  // std::cout << "Buffer size is " << buffer->size() << std::endl;
  //
  // auto new_rh = norodb::RowHeader::deserialize(*buffer);
  // std::cout << new_rh->to_string() << std::endl;
  //
  // std::cout << "Done!" << std::endl;

  // norodb::ByteBuffer bb("HELLO");
  //
  // std::cout << "Val is: " << bb.to_string() << std::endl;
  std::cout << "==== Done ====" << std::endl;
}
