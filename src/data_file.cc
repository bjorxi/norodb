#include "data_file.h"

namespace norodb {

DataFile::DataFile(uint32_t file_id, DBDirectory& dir, DBOptions& options)
    : DBFile{file_id, db_dir, options} {
  std::stringstream fname;
  fname << file_id << ".data";

  fs::path data_file_path = db_dir.get_data_dir() / fname.str();

  std::cout << "Opening a file, path: " << data_file_path << std::endl;
  file.open(data_file_path.string(),
            std::ios::in | std::ios::out | std::ios::app | std::ios::ate | std::ios::binary);
}

uint64_t DataFile::write_row(Row& row) {
  write(*(row.serialize()));
  uint32_t row_size = row.size();
  uint64_t row_offset = write_offset;  // save curr offset to have it in the index entry
  write_offset += row_size;

  return row_offset;
}

Row* DataFile::read_row(uint64_t offset) {
  uint64_t temp_offset = offset;
  auto header_buff = ByteBuffer(RowHeader::HEADER_SIZE);
  read(temp_offset, RowHeader::HEADER_SIZE, header_buff);
  auto header = RowHeader::deserialize(header_buff);
  temp_offset += RowHeader::HEADER_SIZE;
  auto row_buff = ByteBuffer(header->get_key_size() + header->get_val_size());
  read(temp_offset, header->get_key_size() + header->get_val_size(), row_buff);
  auto row = Row::deserialize(row_buff, header->get_key_size(), header->get_val_size());
  row->set_header(*header);

  return row;
}


} // namespace norodb
