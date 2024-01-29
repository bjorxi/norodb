#include "index_file.h"

namespace norodb {

IndexFile::IndexFile(uint32_t file_id, DBDirectory& dir, DBOptions& options)
    : DBFile{file_id, dir, options} {
  std::stringstream fname;
  fname << file_id << ".index";

  fs::path index_file_path = db_dir.get_index_dir() / fname.str();
  std::cout << "Opening a file, path: " << index_file_path << std::endl;

  file.open(index_file_path.string(),
            std::ios::in | std::ios::out | std::ios::app | std::ios::ate | std::ios::binary);

  std::cout << "[IndexFile::IndexFile] write offset " << file.tellp() << std::endl;
  write_offset = file.tellp();
}

IndexFile::IndexFile(fs::path fpath, DBDirectory& dir, DBOptions& options)
  : DBFile{0, dir, options} {
  file.open(fpath,
            std::ios::in | std::ios::out | std::ios::app | std::ios::binary);
  std::cout << "[IndexFile::IndexFile::2] write offset " << file.tellp() << std::endl;
  write_offset = file.tellp();
}

std::tuple<std::shared_ptr<ByteBuffer>, std::shared_ptr<IndexEntry>> IndexFile::read_entry(uint64_t offset) {
  // offset = 45;
  std::cout << "[IndexFile::read_entry] offset " << offset << std::endl;
  auto header_buff = ByteBuffer(IndexEntryHeader::SIZE);
  read(offset, IndexEntryHeader::SIZE, header_buff);
  auto header = IndexEntryHeader::deserialize(header_buff);
  std::cout << "[IndexFile::read_entry] Header size: " << header_buff.size() << ", " << *header << std::endl;

  offset += IndexEntryHeader::SIZE;
  std::cout << "[IndexFile::read_entry] offset " << offset << std::endl;

  std::shared_ptr<ByteBuffer> key_buff = std::make_shared<ByteBuffer>(header->get_key_size());
  std::cout << "[IndexFile::read_entry] key_buff capacity " << key_buff->capacity() << std::endl;
  read(offset, header->get_key_size(), *key_buff);
  std::cout << "[IndexFile::read_entry] key_buff size " << key_buff->size() << std::endl;
  std::cout << "[IndexFile::read_entry] key " << key_buff->to_string() << std::endl;

  offset += header->get_key_size();
  std::cout << "[IndexFile::read_entry] offset " << offset << std::endl;
  auto entry_buff = ByteBuffer(IndexEntry::SIZE);
  read(offset, IndexEntry::SIZE, entry_buff);
  auto entry = IndexEntry::deserialize(entry_buff);

  offset += IndexEntry::SIZE;
  std::cout << "[IndexFile::read_entry] entry " << *entry << " | offset " << offset << std::endl;

  return {key_buff, entry};
}

// void IndexFile::read_entry(uint64_t offset, ByteBuffer& key_buff, IndexEntry& entry) {
//   uint64_t temp_offset = offset;

//   auto header_buff = ByteBuffer(IndexEntryHeader::SIZE);
//   read(temp_offset, IndexEntryHeader::SIZE, header_buff);
//   auto header = IndexEntryHeader::deserialize(header_buff);

//   temp_offset += IndexEntryHeader::SIZE;

//   // auto key_buff = ByteBuffer(header->get_key_size());
//   // std::shared_ptr<ByteBuffer> key_buff = std::make_shared<ByteBuffer>(header->get_key_size());
//   read(temp_offset, header->get_key_size(), key_buff);

//   auto entry_buff = ByteBuffer(IndexEntry::SIZE);
//   read(temp_offset, IndexEntry::SIZE, entry_buff);

//   // auto entry = IndexEntry::deserialize(entry_buff);
//   entry.set_file_id(entry_buff.get_long());
//   entry.set_val_offset(entry_buff.get());
//   entry.set_val_size(entry_buff.get());
//   entry.set_seq_num(entry_buff.get_long());
// }

} // namespace norodb
