#include "cfilewriter.h"

CFileWriter::CFileWriter(string input_file_name) {
  fin.open("");
  if (!fin.is_open())
    throw(string("Cannot open input file: " + input_file_name));
}

CFileWriter::~CFileWriter() {
  fin.close();
}
