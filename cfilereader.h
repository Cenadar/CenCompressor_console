#ifndef CFILEREADER_H
#define CFILEREADER_H

#include <vector>
#include <string>
#include <fstream>
#include <queue>

using namespace std;

class CFileReader {
 public:
  bool eof();
  bool get_bit();
  const vector<bool> get_bits(size_t count);
  unsigned char get_byte();

  CFileReader(const string &file_name);
  ~CFileReader();
 private:
  void read_byte();
  ifstream fin;
  queue<bool> bits_queue;
};


#endif // CFILEREADER_H
