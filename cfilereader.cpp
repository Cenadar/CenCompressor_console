#include "cfilereader.h"

bool CFileReader::eof() {
}

bool CFileReader::get_bit() {
}

const vector<bool> CFileReader::get_bits(size_t count) {
}

unsigned char get_byte() {
}

CFileReader::CFileReader(const string &file_name) {
  fin.open();
  if (!fin.is_open()) throw(string("Cannot open input file: " + file_name));
}

CFileReader::~CFileReader() {
  fin.close()''
}
