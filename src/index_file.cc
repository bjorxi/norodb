#include "index_file.h"

namespace norodb {

IndexFile::IndexFile(uint32_t file_id, DBDirectory& dir, DBOptions& options)
    : DBFile{file_id, dir, options} {
  std::stringstream fname;
  fname << file_id << ".index";

  fs::path index_file_path = db_dir.get_index_dir() / fname.str();

  file.open(index_file_path.string(),
            std::ios::in | std::ios::out | std::ios::app | std::ios::ate | std::ios::binary);

  write_offset = file.tellp();
}

IndexFile::IndexFile(fs::path fpath, DBDirectory& dir, DBOptions& options)
  : DBFile{0, dir, options} {
  file.open(fpath,
            std::ios::in | std::ios::out | std::ios::app | std::ios::binary);
  write_offset = file.tellp();
}

std::tuple<std::shared_ptr<ByteBuffer>, std::shared_ptr<IndexEntry>> IndexFile::read_entry(uint64_t offset) {
  auto header_buff = ByteBuffer(IndexEntryHeader::SIZE);
  read(offset, IndexEntryHeader::SIZE, header_buff);
  auto header = IndexEntryHeader::deserialize(header_buff);

  offset += IndexEntryHeader::SIZE;

  std::shared_ptr<ByteBuffer> key_buff = std::make_shared<ByteBuffer>(header->get_key_size());
  read(offset, header->get_key_size(), *key_buff);

  offset += header->get_key_size();
  auto entry_buff = ByteBuffer(IndexEntry::SIZE);
  read(offset, IndexEntry::SIZE, entry_buff);
  auto entry = IndexEntry::deserialize(entry_buff);

  offset += IndexEntry::SIZE;

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
