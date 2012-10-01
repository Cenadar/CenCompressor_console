// TODO: correct work with empty file

#include "ccompressor.h"
#include "cfilereader.h"
#include "cfilewriter.h"

void CCompressor::ForEachChar(CAbstractCharDoer *Doer) {
  Doer->Init();
  CFileReader *FR = new CFileReader(input_file_name);
  while(!FR->eof()) Doer->Do(FR->get_byte());
  delete FR;
  Doer->Close();
  delete Doer;
}

void CCompressor::compress(const string &input_file_name_,
                           const string &output_file_name_) {
  input_file_name = input_file_name_;
  output_file_name = output_file_name_;
  FW = new CFileWriter(output_file_name);
  CFileWriterCloser FWC(FW);

  ForEachChar(new CDoerCalculateFrequency(this));
  HuffTree.build(frequency);

  write_information_byte();
  write_tree();
  ForEachChar(new CDoerReplaceWithCodes);
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
      FW->put_byte(HuffTree.get_code(it->first).size());
  }

  for(map<unsigned char, size_t>::iterator it = frequency.begin();
      it != frequency.end(); ++it) {
      FW->put_bits(HuffTree.get_code(it->first));
  }
}

void CDoerReplaceWithCodes::Do(unsigned char c) {
  Compressor->FW->put_bits(Compressor->HuffTree.get_code(c));
}

void CDoerCalculateFrequency::Close() {
  Compressor->frequency = frequency;
}
