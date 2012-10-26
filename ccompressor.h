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


class ICompressor {
 public:
  virtual ~ICompressor() {}

  virtual void compress() = 0;
  virtual void uncompress() = 0;
};


class CCompressor: public ICompressor {
 public:
  typedef int key_type;

  static const key_type UseLogger = 0x0001;
  static const key_type DeleteReader = 0x0002;
  static const key_type DeleteWriter = 0x0004;
  static const key_type DeleteLogger = 0x0008;

  CCompressor(IByteReader *BR_,
              IByteWriter *BW_,
              ILogger *logger_,
              key_type options_):
    BR(new CBitReader(BR_)),
    BW(new CBitWriter(BW_)),
    logger(logger_),
    options(options_) {}

  ~CCompressor();

  void compress();
  void uncompress();
 private:
  void write_information_byte();
  void write_tree();
  void read_information_byte();
  void read_tree();

  size_t unused_bits;
  IBitReader *BR;
  IBitWriter *BW;
  ILogger *logger;
  key_type options;
  map<unsigned char, size_t> frequency;
  CHuffmanTree HuffTree;
};

#endif // CCOMPRESSOR_H
