#include "chuffmantree.h"

CHuffmanTree::~CHuffmanTree() {
  erase();
}

struct comp {
  bool operator()(const PTree a, const PTree b) {
    return a->times > b->times;
  }
};

void CHuffmanTree::build(const map<unsigned char, size_t> &frequency) {
  erase();
  if (frequency.empty()) return;

  priority_queue<PTree, vector<PTree>, comp> char_queue;
  for(map<unsigned char, size_t>::const_iterator it = frequency.begin();
      it != frequency.end(); ++it) {
        PTree char_node = new TTree(NULL, NULL, it->first, it->second);
        char_queue.push(char_node);
    }

  PTree char1, char2;
  while(char_queue.size() >= 2) {
    char1 = char_queue.top();  char_queue.pop();
    char2 = char_queue.top();  char_queue.pop();
    char_queue.push(new TTree(char1, char2));
  }
  root = char_queue.top();
  input_file_length = root->times;
  DFS(root, new vector<bool>);
}

void CHuffmanTree::build(const map<unsigned char, vector<bool> > &code) {
  erase();

  /*vector<bool>::iterator it =
  DFS_set(root, it v, .end());*/
}

void CHuffmanTree::erase() {
  result_bits_count = 0;
  erase(root);
  root = NULL;
}

void CHuffmanTree::erase(PTree node) {
  if (node != NULL) {
    erase(node->left);
    erase(node->right);
    delete node;
  }
}

const vector<bool> &CHuffmanTree::get_code(unsigned char curchar) {
  return char_code[curchar];
}

void CHuffmanTree::DFS(PTree vertex, vector<bool> *code) {
  if (vertex->left == NULL) {
    result_bits_count += code->size()*vertex->times;
    char_code[vertex->data] = *code;
  } else {
    code->push_back(0);
    DFS(vertex->left, code);
    code->pop_back();

    code->push_back(1);
    DFS(vertex->right, code);
    code->pop_back();
  }
  if (code->empty()) delete code;
}
