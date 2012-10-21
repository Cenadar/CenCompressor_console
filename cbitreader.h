#ifndef CFILEREADER_H
#define CFILEREADER_H

#include <vector>
#include <string>
#include <fstream>
#include <queue>

using namespace std;

class IByteReader {
 public:
  virtual bool eof() = 0;
  virtual unsigned char next_byte() = 0;
  virtual void reload() {
    close();
    open();
  } 
  virtual void open() = 0;
  virtual void close() = 0;
};


class CFileByteReader: public IByteReader {
 public:
  CFileByteReader(const string& file_name_): file_name(file_name_) {open();}
  ~CFileByteReader() {close();}

  bool eof();
  unsigned char next_byte();
  void open();
  void close();
 private:
  string file_name;
  ifstream fin;
};


class CBitReader {
 public:
  CBitReader(IByteReader *byte_reader_): byte_reader(byte_reader_) {}
  ~CBitReader() {}

  bool eof();
  bool get_bit();
  const vector<bool> get_bits(size_t count);
  unsigned char get_byte();

  void read_byte();

  void open() {byte_reader->open();}
  void close() {byte_reader->close();}
  void reload() {byte_reader->reload();}
 private:
  IByteReader *byte_reader;
  queue<bool> bits_queue;
};

#endif // CFILEREADER_H
