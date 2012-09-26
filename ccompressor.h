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

using namespace std;

class CCompressor {
 public:
  CCompressor() {}
  ~CCompressor() {}
  void compress(const string &input_file_name, const string &output_file_name);
 private:
  map<char, size_t> frequency;
  void write_tree(ofstream &fout);
  void send_to_file(queue<bool> *bit_queue, ofstream &fout);
  static const size_t block_size = 100;
  CHuffmanTree HuffTree;
  string in_file_name, out_file_name;
};

#endif // CCOMPRESSOR_H
