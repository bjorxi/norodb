#include <iostream>

#include "db.h"

int main() {
  norodb::DBOptions opts;
  norodb::DB db("dbdir", opts);

  norodb::ByteArr key;
  norodb::ByteArr val;

  db.put(key, val);

  std::cout << "Done!" << std::endl;
}
