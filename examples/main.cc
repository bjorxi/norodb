#include <filesystem>
#include <iostream>

#include "byte_buffer.h"
#include "db.h"
#include "row.h"
#include "db_file.h"

namespace fs = std::filesystem;

int main() {
  norodb::DBOptions opts;
  norodb::DB db("", opts);
  db.open();
  norodb::ByteBuffer key("key");
  norodb::ByteBuffer val("val");

  db.put(key, val);

  norodb::ByteBuffer key2("key2");
  norodb::ByteBuffer val2("val2");

  db.put(key2, val2);

  norodb::ByteBuffer key3("hello");
  norodb::ByteBuffer val3("world");

  db.put(key3, val3);

  norodb::ByteBuffer key4("key");
  norodb::ByteBuffer val4("noval");

  db.put(key4, val4);



  norodb::ByteBuffer k("hello");
  db.get(k);

  std::cout << "==== Done ====" << std::endl;
}
