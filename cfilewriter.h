#ifndef CFILEWRITER_H
#define CFILEWRITER_H

#include <vector>
#include <string>

class CFileWriter {
 public:
  bool eof();
  bool get_bit();
  unsigned char get_byte();
  const vector<bool>& get_bits(size_ t count);

  CFileWriter(string input_file_name);
  ~CFileWriter();
 private:
  ifstream fin;
  queue<bool> q;
};

#endif // CFILEWRITER_H
