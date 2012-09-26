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
  tagTree(tagTree *left_, tagTree *right_, char data_): left(left_),
                                                        right(right_),
                                                        data(data_) {}
  tagTree(tagTree *left_, tagTree *right_): left(left_),
                                            right(right_),
                                            data(abstract_char_value) {}
  tagTree(): left(NULL),
             right(NULL),
             data(abstract_char_value) {}
} TTree, *PTree;

class CHuffmanTree {
 public:
  CHuffmanTree(): root(NULL),
                  input_file_length_count(0),
                  result_file_length(0) {}
  ~CHuffmanTree();
  bool empty();
  void build(const map<char, size_t> &frequency);  
  void erase();
  const vector<bool> &get_code(char curchar);
 private:
  void DFS(PTree vertex, vector<bool> *code);
  void erase(PTree node);

  map<char, vector<bool> > char_code;
  PTree root;
  size_t input_file_length_count;
  size_t result_file_length;
};

#endif // CHUFFMANTREE_H
