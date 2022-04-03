#include <iostream>

#include "db.h"
#include "row.h"

int main() {
  // norodb::DBOptions opts;
  // norodb::DB db("", opts);
  // db.open();
  //
  // norodb::ByteArr key;
  // norodb::ByteArr val;
  //
  // db.put(key, val);

  norodb::RowHeader rh(1,2,3,4,5);
  auto buffer = rh.serialize();
  std::cout << "Buffer size is " << buffer->size() << std::endl;

  std::cout << "Done!" << std::endl;
}
