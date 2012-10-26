#ifndef CBITREADER_H
#define CBITREADER_H

#include <vector>
#include <string>
#include <fstream>
#include <queue>

using namespace std;

class IByteReader {
 public:
  virtual ~IByteReader() {}
  virtual bool eof() = 0;
  virtual unsigned char next_byte() = 0;
  virtual void open() = 0;
  virtual void close() = 0;
  virtual void reload() = 0;
};


class CFileByteReader: public IByteReader {
 public:
  CFileByteReader(const string& file_name_): file_name(file_name_) {open();}
  ~CFileByteReader() {close();}

  bool eof();
  unsigned char next_byte();
  void open();
  void close();
  void reload();
 private:
  string file_name;
  ifstream fin;
};


class IBitReader {
 public:
  virtual ~IBitReader() {}

  virtual bool eof() = 0;
  virtual bool get_bit() = 0;
  virtual const vector<bool> get_bits(size_t count) = 0;
  virtual unsigned char get_byte() = 0;

  virtual void open() = 0;
  virtual void close() = 0;
  virtual void reload() = 0;

 private:
  virtual void read_byte() = 0;
};


class CBitReader: public IBitReader {
 public:
  CBitReader(IByteReader *byte_reader_): byte_reader(byte_reader_) {}
  ~CBitReader() {close();}

  bool eof();
  bool get_bit();
  const vector<bool> get_bits(size_t count);
  unsigned char get_byte();

  void open() {byte_reader->open();}
  void close() {delete byte_reader;}
  void reload() {byte_reader->reload();}
 private:
  void read_byte();

  IByteReader *byte_reader;
  queue<bool> bits_queue;
};

#endif // CBITREADER_H
