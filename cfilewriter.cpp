#include "cfilewriter.h"

void CFileWriter::put_bit(bool bit) {
  q.push(bit);
  try_put();
}

void CFileWriter::put_bits(const vector<bool> &bits) {
  for(size_t i = 0; i < bits.size(); ++i) q.push(bits[i]);
  try_put();
}

void CFileWriter::put_byte(unsigned char byte) {
  for(int i = 7; i >= 0; --i) q.push((byte >> i) & 1);
  try_put();
}

void CFileWriter::try_put() {
  while (q.size() >= 8) {
    char byte = 0;
    for(int i = 7; i >= 0; --i) {
      byte ^= q.front() << i;
      q.pop();
    }
    fout.put(byte);
  }
}

CFileWriter::CFileWriter(const string &file_name) {
  fout.open(file_name.c_str(), ios::binary);
  if (!fout.is_open()) throw(string("Cannot open output file: " + file_name));
}

CFileWriter::~CFileWriter() {
  if (!q.empty()) {
    while(q.size() < 8) q.push(0);
    try_put();
  }

  fout.close();
}
