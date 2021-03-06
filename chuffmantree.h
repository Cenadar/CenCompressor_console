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
  bool leaf;
  unsigned char data;
  size_t times;
  tagTree(tagTree *left_, tagTree *right_, char data_, size_t times_):
    left(left_), right(right_), leaf(true), data(data_), times(times_) {}
  tagTree(tagTree *left_, tagTree *right_): left(left_),
                                            right(right_),
                                            leaf(false),
                                            data(abstract_char_value) {
    times = (left != NULL ? left->times : 0) +
            (right != NULL ? right->times : 0);
  }
  tagTree(): left(NULL), right(NULL), leaf(false), data(abstract_char_value) {}
} TTree, *PTree;


class CTreePrivacySaver {
 public:
  CTreePrivacySaver(const PTree vertex_): vertex(vertex_) {}
  CTreePrivacySaver(const CTreePrivacySaver& a): vertex(a.vertex) {}

  void go(bool bit) {
    if (vertex == NULL) throw string("File was damaged");
    if (bit == 0)
      vertex = vertex->left;
    else
      vertex = vertex->right;
  }

  bool leaf() const {
    if (vertex == NULL) throw string("File was damaged");
    return vertex->leaf;
  }

  unsigned char data() const {
    if (vertex == NULL) throw string("File was damaged");
    return vertex->data;
  }
 private:
  PTree vertex;
};


class CHuffmanTreeIterator {
 public:
  CHuffmanTreeIterator():
    vertex(new CTreePrivacySaver(NULL)) {}
  CHuffmanTreeIterator(PTree vertex_):
    vertex(new CTreePrivacySaver(vertex_)) {}
  CHuffmanTreeIterator(const CHuffmanTreeIterator &a):
    vertex(new CTreePrivacySaver(*a.vertex)) {}

  CTreePrivacySaver* operator ->() const {return vertex;}
 private:
  CTreePrivacySaver *vertex;
};


class CHuffmanTree/*: public IHuffmanTree*/ {
 public:
  typedef CHuffmanTreeIterator iterator;

  CHuffmanTree(): root(NULL), result_bits_count(0) {}
  ~CHuffmanTree();

  const iterator begin() const {return iterator(root);}

  void build(const map<unsigned char, size_t> &frequency);
  void build(const map<unsigned char, vector<bool> > &code);

  size_t get_result_bits_count() {return result_bits_count;}
  size_t get_input_file_size() {return input_file_length;}
  const vector<bool>& get_code(unsigned char curchar);
 private:
  void DFS(PTree vertex, vector<bool> *code);
  void DFS_set(PTree vertex, unsigned char cur_char, const vector<bool> &code);
  void erase();
  void erase(PTree node);

  map<unsigned char, vector<bool> > char_code;
  PTree root;
  size_t input_file_length;
  size_t result_bits_count;
};

#endif // CHUFFMANTREE_H
