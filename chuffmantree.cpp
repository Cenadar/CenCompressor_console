#include "chuffmantree.h"

CHuffmanTree::~CHuffmanTree() {
  erase();
}

bool CHuffmanTree::empty() {
  return root == NULL;
}

void CHuffmanTree::build(const map<char, size_t> &frequency) {
  if (!empty()) erase();
  if (frequency.empty()) return;

  typedef pair<size_t, PTree> TCharFreq;
  priority_queue<TCharFreq, vector<TCharFreq>, greater<TCharFreq> > char_queue;
  for(map<char, size_t>::const_iterator it = frequency.begin();
      it != frequency.end(); ++it) {
        PTree char_node = new TTree(NULL, NULL, it->first);
        char_queue.push(make_pair(it->second, char_node));
    }

  TCharFreq char1, char2;
  while(char_queue.size() >= 2) {
    char1 = char_queue.top();
    char_queue.pop();
    char2 = char_queue.top();
    char_queue.pop();
    PTree abstract_char = new TTree(char1.second, char2.second);
    char_queue.push(make_pair(char1.first + char2.first, abstract_char));
  }
  root = char_queue.top().second;
  input_file_length_count = char_queue.top().first;

  DFS(root, new vector<bool>);
}

void CHuffmanTree::erase() {
  result_file_length = 0;
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

const vector<bool> &CHuffmanTree::get_code(char curchar) {
  return char_code[curchar];
}

void CHuffmanTree::DFS(PTree vertex, vector<bool> *code) {
  if (vertex->left == NULL) {
    //result_file_length += code->size()*vertex->times;
    char_code[vertex->data] = *code;
  } else {
    code->push_back(0);
    DFS(vertex->left, code);
    code->pop_back();

    code->push_back(1);
    DFS(vertex->right, code);
    code->pop_back();
  }
  //if (code->empty()) delete code;
}
