#include "cbitreader.h"
#include <iostream>

bool CFileByteReader::eof() {
  return fin.peek() == -1;
}

unsigned char CFileByteReader::next_byte() {
  if (eof()) throw string("Unexpected end of file");
  return fin.get();
}

void CFileByteReader::open() {
  fin.open(file_name.c_str(), ios::binary);
  if (!fin.is_open()) throw string("Cannot open input file: ") + file_name;
}

void CFileByteReader::close() {
  fin.close();
}



bool CBitReader::eof() {
  return bits_queue.empty() && byte_reader->eof();
}

bool CBitReader::get_bit() {
  if (bits_queue.empty()) read_byte();
  bool bit = bits_queue.front();
  bits_queue.pop();
  return bit;
}

const vector<bool> CBitReader::get_bits(size_t count) {
  vector<bool> bits;
  for(size_t i = 0; i < count; ++i) {
    if (bits_queue.empty()) read_byte();
    bits.push_back(bits_queue.front());
    bits_queue.pop();
  }
  return bits;
}

unsigned char CBitReader::get_byte() {
  unsigned char byte = 0;
  for(int i = 7; i >= 0; --i) {
    if (bits_queue.empty()) read_byte();
    byte ^= (unsigned char)bits_queue.front() << i;
    bits_queue.pop();
  }
  return byte;
}

void CBitReader::read_byte() {
  unsigned char byte = byte_reader->next_byte();
  for(int i = 7; i >= 0; --i) bits_queue.push((byte >> i) & 1);
}
