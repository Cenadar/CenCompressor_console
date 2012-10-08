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
#include "cfilereader.h"
#include "cfilewriter.h"

using namespace std;

class CCompressor {
 public:
  CCompressor() {}
  ~CCompressor() {}
  void compress(const string &input_file_name,
                const string &output_file_name);
  void uncompress(const string &input_file_name,
                  const string &output_file_name);
 private:
  void write_information_byte();
  void write_tree();
  void read_tree();

  CFileReader *FR;
  CFileWriter *FW;
  map<unsigned char, size_t> frequency;
  CHuffmanTree HuffTree;
};

#endif // CCOMPRESSOR_H
