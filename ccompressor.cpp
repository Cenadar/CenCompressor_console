// TODO: correct work with empty file

#include "ccompressor.h"
#include "cfilereader.h"
#include "cfilewriter.h"

class CFileReaderCloser {
 public:
  CFileReaderCloser(CFileReader *FR_): FR(FR_) {}
  ~CFileReaderCloser() {delete FR;}
 private:
  CFileReader *FR;
};

class CFileWriterCloser {
 public:
  CFileWriterCloser(CFileWriter *FW_): FW(FW_) {}
  ~CFileWriterCloser() {delete FW;}
 private:
  CFileWriter *FW;
};

// Compressing

void CCompressor::compress(const string &input_file_name,
                           const string &output_file_name) {  
  FW = new CFileWriter(output_file_name);
  CFileWriterCloser FWC(FW);

  frequency.clear();
  FR = new CFileReader(input_file_name);
  while(!FR->eof()) ++frequency[FR->get_byte()];
  delete FR;
  HuffTree.build(frequency);

  write_information_byte();
  write_tree();

  FR = new CFileReader(input_file_name);
  while(!FR->eof()) FW->put_bits(HuffTree.get_code(FR->get_byte()));
  delete FR;

  cout << "Compressed succesffully" << endl;
  cout << "Input file size: " << HuffTree.get_input_file_size() << endl;
  cout << "Output file size: ";
  cout << 1 + 32 + (HuffTree.get_result_bits_count() + 7)/8 << endl;
}

void CCompressor::write_information_byte() {
  unsigned char byte = 0;
  byte ^= (unsigned char)(HuffTree.get_result_bits_count() & 7);
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

void CCompressor::uncompress(const string &input_file_name,
                             const string &output_file_name) {
  FR = new CFileReader(input_file_name);
  CFileReaderCloser FRC(FR);
  FW = new CFileWriter(output_file_name);
  CFileWriterCloser FWC(FW);

  unsigned char inform_byte = FR->get_byte();
  read_tree();
}

void CCompressor::read_tree() {
  vector<bool> used = FR->get_bits(256);
  map<unsigned char, unsigned char> code_length;
  map<unsigned char, vector<bool> > codes;

  for(unsigned int i = 0; i < 256; ++i)
    if (used[i])
      code_length[i] = FR->get_byte();

  for(unsigned int i = 0; i < 256; ++i)
    if (used[i])
      codes[i] = FR->get_bits(code_length[i]);

  HuffTree.build(codes);
}
