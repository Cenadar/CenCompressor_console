#ifndef CBITWRITER_H
#define CBITWRITER_H

#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <cassert>

using namespace std;

class IByteWriter {
 public:
  virtual ~IByteWriter() {}

  virtual void put(unsigned char c) = 0;
  virtual void open() = 0;
  virtual void close() = 0;
};


class CFileByteWriter: public IByteWriter {
 public:
  CFileByteWriter(const string& file_name_): file_name(file_name_) {open();}
  ~CFileByteWriter() {close();}

  void put(unsigned char c);
 private:
  void open();
  void close();

  string file_name;
  ofstream fout;
};


class CBitWriter {
 public:
  void put_bit(bool bit);
  void put_byte(unsigned char byte);
  void put_bits(const vector<bool> &bits);

  CBitWriter(IByteWriter *byte_writer_): byte_writer(byte_writer_) {}
  ~CBitWriter();
 private:
  void try_put();

  IByteWriter *byte_writer;
  queue<bool> q;
};

#endif // CBITWRITER_H
