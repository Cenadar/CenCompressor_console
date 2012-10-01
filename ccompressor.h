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

typedef unsigned char uchar;

class CCompressor;

class CAbstractCharDoer {
 public:
  virtual void Init() = 0;
  virtual void Do(char c) = 0;
};

class CDoerCalculateFrequency: public CAbstractCharDoer {
 public:
  void Init() {frequency.clear();}
  void Do(char c) {++frequency[c];}

  const map<char, size_t> &get_frequency() {return frequency;}
 private:
  map<char, size_t> frequency;
};

class CDoerReplaceWithCodes: public CAbstractCharDoer {
 public:
  void Init() {}
  void Do(char c);
  CCompressor *Compressor;
  void set_compressor(const CCompressor &Compr_) {
    Compressor = (CCompressor*)&Compr_;
  }
};

class CCompressor {
 public:
  CCompressor() {}
  ~CCompressor() {}
  void compress(const string &input_file_name, const string &output_file_name);
 private:
  void ForEachChar(CAbstractCharDoer *Doer);

  void write_information_byte();
  void write_tree();
  void put_byte();

  friend void CDoerReplaceWithCodes::Do(char);

  queue<bool> bit_queue;
  ifstream fin;
  ofstream fout;
  map<char, size_t> frequency;
  static const size_t block_size = 100;
  CHuffmanTree HuffTree;
  string in_file_name, out_file_name;
};

#endif // CCOMPRESSOR_H
