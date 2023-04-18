#include <iostream>

using namespace std;

template <class T>
class BST {
  class BSTNode {
  public:
    BSTNode(const T &v) : val(v) { left = right = NULL; }
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
  
  bool find(const T &v) const {
    BSTNode *walk = root;
    while (walk) {
      if (walk->val == v)
	return true;
      if (v > walk->val)
	walk = walk->right;
      else
	walk = walk->left;
    }
    return false;
  }

  /* delete the element in the tree with value v that is closest to the root */
  void remove(const T &v) {
    BSTNode **cur = &root;
    BSTNode *tmp;
    while (*cur) {
      if (v == (*cur)->val) break;
      if (v < (*cur)->val) cur = &((*cur)->left);
      else cur = &((*cur)->right);
    }
    if (*cur == NULL) /* not found */
      return;

    /* 0-1 child case
    if ((*cur)->left == NULL || (*cur)->right == NULL) {
      tmp = *cur;
      *cur = tmp->left ? tmp->left : tmp->right;
      delete tmp;
      return;
      } */
      
    /* 0 children */
    if ((*cur)->left == NULL && (*cur)->right == NULL) {
      *cur = NULL;
      delete *cur;
      return;
    }
    /* 1 child */
    if ((*cur)->left == NULL) {
      tmp = *cur;
      *cur = tmp->right;
      delete tmp;
      return;
    }
    if ((*cur)->right == NULL) {
      tmp = *cur;
      *cur = tmp->left;
      delete tmp;
      return;
    }
    /* 2 child */
    tmp = *cur; /* victim */
    cur = &((*cur)->left);
    while ((*cur)->right)
      cur = &((*cur)->right);
    /* now *cur points to the rightmost node in the left subtree of victim */
    tmp->val = (*cur)->val;
    if ((*cur)->left == NULL && (*cur)->right == NULL) {
      *cur = NULL;
      delete *cur;
      return;
    }
    /* 1 child */
    if ((*cur)->left == NULL) {
      tmp = *cur;
      *cur = tmp->right;
      delete tmp;
      return;
    }
    
    
    /*
    tmp = (*cur)->left;
    if (!tmp->right) {
      tmp->right = (*cur)->right;
      (*cur)->val = tmp->val;
      
    }
    while (tmp->right && tmp->right->right)
      tmp = tmp->right;
    */
    
  }

  BSTNode *root;
};

int main() {
  BST<int> t;
  t.insert(5);
  t.insert(3);
  t.insert(7);
  
  cout << t.find(5) << endl;
  cout << t.find(3) << endl;
  cout << t.find(7) << endl;

  t.remove(5);
  
  cout << t.find(5) << endl;
  cout << t.find(3) << endl;
  cout << t.find(7) << endl;
  return 0;
}
