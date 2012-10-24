#include "cbitwriter.h"
#include <cassert>

void CFileByteWriter::put(unsigned char c) {
  fout.put(c);
}

void CFileByteWriter::open() {
  fout.open(file_name.c_str(), ios::binary);
  if (!fout.is_open()) throw(string("Cannot open output file: " + file_name));
}

void CFileByteWriter::close() {  
  fout.close();
}



CBitWriter::~CBitWriter() {
  assert((q.size() & 7) == 0);
  if (!q.empty()) {
    while(q.size() < 8) q.push(0);
    try_put();
  }
  delete byte_writer;
}

void CBitWriter::put_bit(bool bit) {
  q.push(bit);
  try_put();
}

void CBitWriter::put_bits(const vector<bool> &bits) {
  for(size_t i = 0; i < bits.size(); ++i) q.push(bits[i]);
  try_put();
}

void CBitWriter::put_byte(unsigned char byte) {
  for(int i = 7; i >= 0; --i) q.push((byte >> i) & 1);
  try_put();
}

void CBitWriter::try_put() {
  while (q.size() >= 8) {
    char byte = 0;
    for(int i = 7; i >= 0; --i) {
      byte ^= q.front() << i;
      q.pop();
    }
    byte_writer->put(byte);
  }
}
