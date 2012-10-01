#ifndef CHUFFMANTREE_H
#define CHUFFMANTREE_H

#include <cstdlib>
#include <cassert>
#include <vector>
#include <string>
#include <queue>
#include <map>

#include <iostream>

using namespace std;

const char abstract_char_value = '\0';

typedef struct tagTree {
  tagTree *left, *right;
  char data;
  size_t times;
  tagTree(tagTree *left_, tagTree *right_, char data_, size_t times_):
    left(left_), right(right_), data(data_), times(times_) {}
  tagTree(tagTree *left_, tagTree *right_): left(left_),
                                            right(right_),
                                            data(abstract_char_value) {
    times = (left != NULL ? left->times : 0) +
            (right != NULL ? right->times : 0);
  }  
  bool operator()(const tagTree *a, const tagTree *b) {
    return a->times > b->times;
  }
} TTree, *PTree;

class CHuffmanTree {
 public:
  CHuffmanTree(): root(NULL),
                  result_bits_count(0) {}
  ~CHuffmanTree();
  bool empty();
  void build(const map<unsigned char, size_t> &frequency);
  void erase();

  size_t get_result_bits_count() {return result_bits_count;}
  const vector<bool> &get_code(unsigned char curchar);
 private:
  void DFS(PTree vertex, vector<bool> *code);
  void erase(PTree node);

  map<char, vector<bool> > char_code;
  PTree root;
  size_t input_file_length;
  size_t result_bits_count;
};

#endif // CHUFFMANTREE_H
