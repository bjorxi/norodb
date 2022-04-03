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
    void getBytes(uint8_t* buf, uint32_t len);
    char getChar();
    char getChar(uint32_t index); // Absolute
    double getDouble();
    double getDouble(uint32_t index);
    float getFloat();
    float getFloat(uint32_t index);
    uint32_t getInt();
    uint32_t getInt(uint32_t index);
    uint64_t getLong();
    uint64_t getLong(uint32_t index);
    uint16_t getShort();
    uint16_t getShort(uint32_t index);

    void put(ByteBuffer* src);
    void put(uint8_t b);
    void put(uint8_t b, uint32_t index);
    void putBytes(uint8_t* b, uint32_t len);
    void putBytes(uint8_t* b, uint32_t len, uint32_t index);
    void putChar(char value);
    void putChar(char value, uint32_t index);
    void putDouble(double value);
    void putDouble(double value, uint32_t index);
    void putFloat(float value);
    void putFloat(float value, uint32_t index);
    void putInt(uint32_t value);
    void putInt(uint32_t value, uint32_t index);
    void putLong(uint64_t value);
    void putLong(uint64_t value, uint32_t index);
    void putShort(uint16_t value);
    void putShort(uint16_t value, uint32_t index);
};

} // namespace norodb

#endif
