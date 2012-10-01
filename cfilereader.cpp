#include "cfilereader.h"

bool CFileReader::eof() {
  return fin.eof();
}

CFileReader::get_bit() {
}

CFileReader::CFileReader() {
  fin.open("");
  if (!fin.is_open())
    throw(string("Cannot open input file: " + input_file_name));
}
