#ifndef CFILEREADER_H
#define CFILEREADER_H

#include <vector>
#include <string>

class CFileReader {
 public:
  bool eof();
  bool get_bit();
  char get_byte();
  const vector<bool>& get_bits(size_ t count);

  CFileReader(string input_file_name);
  ~CFileReader();
 private:
  ifstream fin;
  queue<bool> q;
};


#endif // CFILEREADER_H
