#ifndef NORO_DB_BYTE_BUFFER_H_
#define NORO_DB_BYTE_BUFFER_H_

#include <cstdint>
#include <vector>

#define DEFAULT_CAPACITY 256
#define INT_SIZE 4
#define LONG_SIZE 8

namespace norodb {

class ByteBuffer {
  std::vector<uint8_t> buff;
  uint32_t wpos = 0;
  uint32_t rpos = 0;

  public:
    ByteBuffer();
    ByteBuffer(uint32_t size);

    void clear() {wpos=0; rpos=0; buff.clear();};
    uint32_t size() {return wpos;};
    uint32_t capacity() {return buff.size();};
    void grow() {buff.resize(buff.size()*2);};

    uint8_t get();
    uint8_t get(uint32_t index);
    void get_bytes(uint8_t* buf, uint32_t len);
    char get_char();
    char get_char(uint32_t index); // Absolute
    double get_double();
    double get_double(uint32_t index);
    float get_float();
    float get_float(uint32_t index);
    uint32_t get_int();
    uint32_t get_int(uint32_t index);
    uint64_t get_long();
    uint64_t get_long(uint32_t index);
    uint16_t get_short();
    uint16_t get_short(uint32_t index);

    void put(ByteBuffer* src);
    void put(uint8_t b);
    void put(uint8_t b, uint32_t index);
    void put_bytes(uint8_t* b, uint32_t len);
    void put_bytes(uint8_t* b, uint32_t len, uint32_t index);
    void put_char(char value);
    void put_char(char value, uint32_t index);
    void put_double(double value);
    void put_double(double value, uint32_t index);
    void put_float(float value);
    void put_float(float value, uint32_t index);
    void put_int(uint32_t value);
    void put_int(uint32_t value, uint32_t index);
    void put_long(uint64_t value);
    void put_long(uint64_t value, uint32_t index);
    void put_short(uint16_t value);
    void put_short(uint16_t value, uint32_t index);
};

} // namespace norodb

#endif
