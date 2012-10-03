#include "cfilereader.h"

#include <iostream>

bool CFileReader::eof() {
  return bits_queue.empty() && fin.peek() == -1;
}

bool CFileReader::get_bit() {
  if (bits_queue.empty()) read_byte();
  bool bit = bits_queue.front();
  bits_queue.pop();
  return bit;
}

const vector<bool> CFileReader::get_bits(size_t count) {  
  vector<bool> bits;
  for(size_t i = 0; i < count; ++i) {
    if (bits_queue.empty()) read_byte();
    bits.push_back(bits_queue.front());
    bits_queue.pop();
  }
  return bits;
}

unsigned char CFileReader::get_byte() {  
  unsigned char byte = 0;
  for(int i = 7; i >= 0; --i) {
    if (bits_queue.empty()) read_byte();
    byte ^= (unsigned char)bits_queue.front() << i;
    bits_queue.pop();
  }
  return byte;
}

void CFileReader::read_byte() {
  unsigned char byte;
  byte = fin.get();
  for(int i = 7; i >= 0; --i) bits_queue.push((byte >> i) & 1);
}

CFileReader::CFileReader(const string &file_name) {
  fin.open(file_name.c_str(), ios::binary);
  if (!fin.is_open()) throw(string("Cannot open input file: " + file_name));
}

CFileReader::~CFileReader() {
  fin.close();
}
