#ifndef CFILEWRITER_H
#define CFILEWRITER_H

#include <vector>
#include <string>

class CFileWriter {
 public:
  void put_bit(bool bit);
  void put_byte(unsigned char byte);
  void put_bits(const vector<bool>& bits);

  CFileWriter(string file_name);
  ~CFileWriter();
 private:
  void try_put();

  ofstream fout;
  queue<bool> q;
};

#endif // CFILEWRITER_H
