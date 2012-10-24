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
#include "cbitwriter.h"
#include "logger.h"

using namespace std;

class CCompressor {
 public:
  CCompressor(IByteReader *BR_, IByteWriter *BW_, ILogger *logger_):
    BR(BR_), BW(BW_), logger(logger_) {}

  ~CCompressor() {delete logger;}

  void compress();
  void uncompress();
 private:
  void write_information_byte();
  void write_tree();
  void read_information_byte();
  void read_tree();

  size_t unused_bits;
  CBitReader BR;
  CBitWriter BW;
  map<unsigned char, size_t> frequency;
  CHuffmanTree HuffTree;

  ILogger *logger;
};

#endif // CCOMPRESSOR_H
