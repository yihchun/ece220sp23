#include <iostream>
#include <stack>
#include <utility>

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

  class BSTIterator : public iterator<forward_iterator_tag, T> {
  public:
    BSTIterator() { }
    BSTIterator(BSTNode *start) {
      while (start) {
	state.push(make_pair(start, false));
	start = start->left;
      }
    }
    BSTIterator(const BSTIterator &x) { state = x.state; }
    BSTIterator &operator=(const BSTIterator &x) {
      /* probably not needed: while (!state.empty()) state.pop(); */
      state = x.state;
      return *this;
    }
    BSTIterator &operator++() { step(); return *this; }
    BSTIterator operator++(int) { BSTIterator tmp(*this); step(); return tmp; }
    bool operator==(const BSTIterator &x) { return state == x.state; }
    bool operator!=(const BSTIterator &x) { return state != x.state; }
    const T &operator*() const { return state.top().first->val; }

  private:
    void step() {
      BSTNode *tmp;
      if (state.empty()) return;
      if ((state.top().second == false) && (state.top().first->right != NULL)) {
	state.top().second = true;
	for (tmp = state.top().first->right; tmp; tmp = tmp->left)
	  state.push(make_pair(tmp, false));
	return;
      }
      do {
	state.pop();
      } while (!state.empty() && state.top().second);
    }
    
    stack<pair<BSTNode *,bool> > state; /* boolean is have you gone right yet */
  };
  
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

    if ((*cur)->left != NULL && (*cur)->right != NULL) {
      tmp = *cur; /* victim */
      cur = &((*cur)->left);
      while ((*cur)->right)
	cur = &((*cur)->right);
      /* now *cur points to the rightmost node in the left subtree of victim */
      tmp->val = (*cur)->val;
    }
      
    tmp = *cur;
    *cur = tmp->left ? tmp->left : tmp->right;
    delete tmp;
  }
  BSTIterator begin() { return BSTIterator(root); }
  BSTIterator end() { return BSTIterator(); }

  BSTNode *root;
};

/*
void traverse(BST<int>::BSTNode *x) {
  if (!x) return;
  traverse(x->left);  // PC = 1
  x->val;             // PC = 2
  traverse(x->right); // PC = 3
}
*/

int main() {
  BST<int> t;
  t.insert(5);
  t.insert(3);
  t.insert(7);
  t.insert(4);
  t.insert(2);
  
  for (auto i: t)
    cout << i << endl;
  
  t.remove(5);
  
  for (auto i: t)
    cout << i << endl;

  return 0;
}
