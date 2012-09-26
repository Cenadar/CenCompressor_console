#include "ccompressor.h"

void push_vector_to_queue(const vector<bool> &vec, queue<bool> *que) {
  for(size_t i = 0; i < vec.size(); ++i) que->push(vec[i]);
}

void CCompressor::compress(const string &input_file_name,
                           const string &output_file_name) {
  ifstream fin(input_file_name.c_str(), ios::binary);
  if (!fin.is_open()) throw("Cannot open input file: " + input_file_name);
  ofstream fout(output_file_name.c_str(), ios::binary);
  if (!fout.is_open()) throw("Cannot open output file: " + output_file_name);

  char *block = new char[block_size + 2];
  if (block == NULL) throw ("Not enought memory to read a piece of the file");
  size_t last_read_size;
  frequency.clear();
  do {
    fin.read(block, block_size);
    last_read_size = fin.gcount();
    for(size_t i = 0; i < last_read_size; ++i) {
      char curchar = block[i];
      ++frequency[curchar];
    }
  } while(last_read_size > 0);

  HuffTree.build(frequency);

  // TODO: Delete duplicate code:
  // ASK: Why seekg isn't working
  // ASK: About chars and transformations

//  fin.seekg(0, ios_base::beg);
  fin.close();
  fin.open(input_file_name.c_str(), ios::binary);
  write_tree(fout);
  queue<bool> bit_queue;
  do {
    fin.read(block, block_size);
    last_read_size = fin.gcount();
    for(size_t i = 0; i < last_read_size; ++i) {
      char curchar = block[i];
      push_vector_to_queue(HuffTree.get_code(curchar), &bit_queue);
      while(bit_queue.size() >= 8) send_to_file(&bit_queue, fout);
    }
  } while(last_read_size > 0);
  send_to_file(&bit_queue, fout);

  fin.close();
  fout.close();
  delete[] block;

  // TODO: correct work with empty file
}

void CCompressor::write_tree(ofstream &fout) {
  vector<bool> used(256, false);
  queue<bool> codes_queue;
  for(map<char, size_t>::iterator it = frequency.begin(); it != frequency.end();
      ++it) {
      used[int(it->first) & 255] = true;
  }
  push_vector_to_queue(used, &codes_queue);
  cerr << endl;
  while(!codes_queue.empty()) send_to_file(&codes_queue, fout);
  cerr << endl;

  for(map<char, size_t>::iterator it = frequency.begin(); it != frequency.end();
      ++it) {
      push_vector_to_queue(HuffTree.get_code(it->first), &codes_queue);
  }
  while(!codes_queue.empty()) send_to_file(&codes_queue, fout);
}

void CCompressor::send_to_file(queue<bool> *bit_queue, ofstream &fout) {
  char curbyte = 0;
  for(int i = 8; i-- && !bit_queue->empty(); ) {
      curbyte ^= bit_queue->front() << i;
      bit_queue->pop();
  }
  fout.put(curbyte);

  // DEBUG:
  cerr << bitset<8>(curbyte).to_string() << endl;
  // /DEBUG
}
