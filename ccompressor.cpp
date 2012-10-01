// ASK: Why seekg don't work
// ASK: About chars and transformations -128..127
// TODO: correct work with empty file

/*  fin.close();
fin.open(input_file_name.c_str(), ios::binary);*/


#include "ccompressor.h"

void push_vector_to_queue(const vector<bool> &vec, queue<bool> *que) {
  for(size_t i = 0; i < vec.size(); ++i) que->push(vec[i]);
}

void CCompressor::ForEachChar(CAbstractCharDoer *Doer) {
  Doer->Init();

  char *block = new char[block_size + 2];
  if (block == NULL) throw (string("Not enought memory to read "
                                   "a piece of the file"));
  size_t last_read_size;
  fin.seekg(0, ios_base::beg);
  do {
    fin.read(block, block_size);
    last_read_size = fin.gcount();
    for(size_t i = 0; i < last_read_size; ++i) Doer->Do(block[i]);
  } while(last_read_size > 0);

  delete[] block;
}

void CCompressor::compress(const string &input_file_name,
                           const string &output_file_name) {
  fin.open(input_file_name.c_str(), ios::binary);
  if (!fin.is_open())
    throw(string("Cannot open input file: " + input_file_name));

  fout.open(output_file_name.c_str(), ios::binary);
  if (!fout.is_open())
    throw(string("Cannot open output file: " + output_file_name));

  while(!bit_queue.empty()) bit_queue.pop();


  CDoerCalculateFrequency *CalcFreq = new CDoerCalculateFrequency;
  ForEachChar(CalcFreq);
  frequency = CalcFreq->get_frequency();
  delete CalcFreq;

  HuffTree.build(frequency);

  write_information_byte();
  write_tree();

  CDoerReplaceWithCodes *CodeReplacer = new CDoerReplaceWithCodes;
  ForEachChar(CodeReplacer);
  delete CodeReplacer;

  if (!bit_queue.empty()) put_byte(); // Put last uncomplete byte;

  fin.close();
  fout.close();  
}

void CCompressor::write_information_byte() {
  char curbyte = 0;
  int get_number_of_result_bits();

  curbyte ^= char(HuffTree.get_result_bits_count() & 7);
  put_byte();
}

void CCompressor::write_tree() {
  vector<bool> used(256, false);
  for(map<char, size_t>::iterator it = frequency.begin(); it != frequency.end();
      ++it) {
      used[int(it->first) & 255] = true;
  }
  push_vector_to_queue(used, &bit_queue);
  while(!bit_queue.empty()) put_byte();

  for(map<char, size_t>::iterator it = frequency.begin(); it != frequency.end();
      ++it) {
      push_vector_to_queue(HuffTree.get_code(it->first), &bit_queue);
  }

  while(!bit_queue.empty()) put_byte();
}

void CCompressor::put_byte() {
  char curbyte = 0;
  for(int i = 8; i-- && !bit_queue.empty(); ) {
      curbyte ^= bit_queue.front() << i;
      bit_queue.pop();
  }
  fout.put(curbyte);
}

void CDoerReplaceWithCodes::Do(char c) {
  push_vector_to_queue(Compressor->HuffTree.get_code(c),
                       &Compressor->bit_queue);
  while(Compressor->bit_queue.size() >= 8) Compressor->put_byte();
}
