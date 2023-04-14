#include <iostream>

template <class T>
class BST {
  class BSTNode {
  public:
    BSTNode(const T &v) : val(v) { left = right = NULL);
    BSTNode *left;
    BSTNode *right;
    T val;
  };
public:
  BST() { root = NULL; }
  void insert(const T &v) {
    BSTNode **cur = &root;
    while (*cur) {
      if (v < (*cur)->val) cur = &((*cur)->left);
      else cur = &((*cur)->right);
    }
    *cur = new BSTNode(v);
  }

  
  BSTNode *root;
  
}
