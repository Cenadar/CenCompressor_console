#ifndef CCOMPRESSOR_H
#define CCOMPRESSOR_H

#include <cstdlib>
#include <cassert>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <fstream>
#include <iostream>
#include <bitset>
#include "chuffmantree.h"
#include "cfilewriter.h"

using namespace std;

class CCompressor;

class CAbstractCharDoer {
 public:
  virtual void Init() = 0;
  virtual void Do(unsigned char c) = 0;
  virtual void Close() = 0;
};

class CDoerCalculateFrequency: public CAbstractCharDoer {
 public:
  void Init() {frequency.clear();}
  void Do(unsigned char c) {++frequency[c];}
  CDoerCalculateFrequency(CCompressor *Compressor_): Compressor(Compressor_) {}  
  void Close();
 private:
  map<unsigned char, size_t> frequency;
  CCompressor *Compressor;
};

class CDoerReplaceWithCodes: public CAbstractCharDoer {
 public:
  void Init() {}
  void Do(unsigned char c);
  void Close() {}
  CDoerReplaceWithCodes(CCompressor *Compressor_): Compressor(Compressor_) {}
 private:
  CCompressor *Compressor;
};

class CFileWriterCloser {
 public:
  CFileWriterCloser(CFileWriter *FW_): FW(FW_) {}
  ~CFileWriterCloser() {delete FW;}
 private:
  CFileWriter *FW;
};

class CCompressor {
 public:
  CCompressor() {}
  ~CCompressor() {}
  void compress(const string &input_file_name_,
                const string &output_file_name_);
 private:
  string input_file_name;
  string output_file_name;
  CFileWriter *FW;

  void ForEachChar(CAbstractCharDoer *Doer);

  void write_information_byte();
  void write_tree();
  void put_byte();

  friend void CDoerCalculateFrequency::Close();
  friend void CDoerReplaceWithCodes::Do(unsigned char);

  map<unsigned char, size_t> frequency;
  static const size_t block_size = 100;
  CHuffmanTree HuffTree;
  string in_file_name, out_file_name;
};

#endif // CCOMPRESSOR_H
