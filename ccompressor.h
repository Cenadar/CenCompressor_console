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
#include "cbitreader.h"
#include "cfilewriter.h"
#include "logger.h"

using namespace std;

class CCompressor {
 public:
  CCompressor(IByteReader *BR_, ILogger *logger_): BR(BR_), logger(logger_) {}
  ~CCompressor() {}
  void compress(const string &output_file_name);
  void uncompress(const string &output_file_name);
 private:
  void write_information_byte();
  void write_tree();
  void read_information_byte();
  void read_tree();

  size_t unused_bits;
  CBitReader BR;
  CFileWriter *FW;
  map<unsigned char, size_t> frequency;
  CHuffmanTree HuffTree;

  ILogger *logger;
};

#endif // CCOMPRESSOR_H
