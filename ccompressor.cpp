// TODO: correct work with empty file

#include "ccompressor.h"
#include "cbitreader.h"
#include "cfilewriter.h"
#include <cstdlib>

class CBitReaderCloser {
 public:
  CBitReaderCloser(CBitReader *BR_): BR(BR_) {}
  ~CBitReaderCloser() {delete BR;}
 private:
  CBitReader *BR;
};

class CFileWriterCloser {
 public:
  CFileWriterCloser(CFileWriter *FW_): FW(FW_) {}
  ~CFileWriterCloser() {delete FW;}
 private:
  CFileWriter *FW;
};

// Compressing

void CCompressor::compress(const string &output_file_name) {
  try {
    FW = new CFileWriter(output_file_name);
    CFileWriterCloser FWC(FW);

    // Calculating
    frequency.clear();
    BR.reload();
    while(!BR.eof()) ++frequency[BR.get_byte()];
    HuffTree.build(frequency);

    // Replacing
    write_information_byte();
    write_tree();
    FW->put_bits(vector<bool>(unused_bits, false));

    BR.reload();
    while(!BR.eof()) FW->put_bits(HuffTree.get_code(BR.get_byte()));    

    // Logging
    logger->log("Compressed succesffully");
    logger->log("Input file size: " +
                itoa(HuffTree.get_input_file_size()));
    logger->log("Output file size: " +
                itoa((HuffTree.get_result_bits_count() + 7)/8));
  } catch(string error_message) {
    cout << "ERROR! Compress failed: " << endl;
    cout << error_message << endl;
  }
}

void CCompressor::write_information_byte() {
  unsigned char byte = 0;
  size_t all_result_size = HuffTree.get_result_bits_count();  
  unused_bits = (8 - (all_result_size & 7)) & 7;
  byte ^= (unsigned char)(unused_bits << 0);
  FW->put_byte(byte);
}

void CCompressor::write_tree() {
  vector<bool> used(256, false);
  for(map<unsigned char, size_t>::iterator it = frequency.begin();
    it != frequency.end(); ++it) {
    used[int(it->first) & 255] = true;
  }
  FW->put_bits(used);

  for(map<unsigned char, size_t>::iterator it = frequency.begin();
    it != frequency.end(); ++it) {
    FW->put_byte((unsigned char)HuffTree.get_code(it->first).size());
  }

  for(map<unsigned char, size_t>::iterator it = frequency.begin();
    it != frequency.end(); ++it) {
    FW->put_bits(HuffTree.get_code(it->first));
  }
}

// Uncompressing

void CCompressor::uncompress(const string &output_file_name) {
  try {
    FW = new CFileWriter(output_file_name);  CFileWriterCloser FWC(FW);

    read_information_byte();
    read_tree();
    BR.get_bits(unused_bits); // erase unused bits

    while(!BR.eof()) {
      CHuffmanTree::iterator it = HuffTree.begin();
      while(!it.leaf())
        it.go(BR.get_bit());
      FW->put_byte(*it);
    }
  } catch(string error_message) {
    cout << "ERROR! Decompress failed: " << endl;
    cout << error_message << endl;
  }  
}

void CCompressor::read_information_byte() {
  unsigned char byte = BR.get_byte();
  unused_bits = (byte >> 0) & 7;
}

void CCompressor::read_tree() {
  vector<bool> used = BR.get_bits(256);
  map<unsigned char, unsigned char> code_length;
  map<unsigned char, vector<bool> > codes;

  for(unsigned int i = 0; i < 256; ++i)
    if (used[i])
      code_length[i] = BR.get_byte();

  for(unsigned int i = 0; i < 256; ++i)
    if (used[i])
      codes[i] = BR.get_bits(code_length[i]);

  HuffTree.build(codes);
}
