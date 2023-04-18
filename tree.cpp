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

  private:
    void step() {
      BSTNode *tmp;
      /* still working on this part of the code: another special
       * case to deal with here 4/18
       */
      if (stack.top().second == false) {
	stack.top().second = true;
	for (tmp = stack.top()->right; tmp; tmp = tmp->left)
	  state.push(make_pair(tmp, false));
      }
	
    }
    
    stack<pair<BSTNode *,bool>> state; /* boolean is have you gone right yet */
  }
  
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
  
  cout << t.find(5) << endl;
  cout << t.find(3) << endl;
  cout << t.find(7) << endl;

  t.remove(5);
  
  cout << t.find(5) << endl;
  cout << t.find(3) << endl;
  cout << t.find(7) << endl;
  cout << t.find(4) << endl;
  cout << t.find(2) << endl;

  auto it = t.begin();
  cout << *it << endl;
  
  return 0;
}
