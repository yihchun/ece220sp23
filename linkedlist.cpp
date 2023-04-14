#include <iostream>

using namespace std;

template <class T> class List;
template <class T> class ListIterator;

template <class T>
class Node {
private:
  T data;
  Node *next;
  Node(T data_, Node *next_) { data = data_; next = next_; cout << "Creating " << this << endl; }
  ~Node() { cout << "Deleting " << this << endl; }
  friend class List<T>;
  friend class ListIterator<T>;
  friend ostream &operator<<(ostream &os, const List<double> &list);
};
  
template <class T>
class List {
public:
  List() { head = NULL; }
  ~List() {
    Node<T> *tmp;
    for (; head; head = tmp) {
      tmp = head->next;
      delete head;
    }
  }
  List<T> &operator=(const List<T> &src) {
    Node<T> *tmp;
    Node<T> **walk = &head;
    for (; head; head = tmp) {
      tmp = head->next;
      delete head;
    }
    head = NULL;
    for (tmp = src.head; tmp; tmp = tmp->next) {
      *walk = new Node<T>(tmp->data, NULL);
      walk = &((*walk)->next);
    }
    return *this;
  }
  void insert_head(T data) {
    head = new Node<T>(data, head);
  }
  ListIterator<T> begin() const { return ListIterator<T>(head); }
  ListIterator<T> end() const { return ListIterator<T>(NULL); }
private:
  Node<T> *head;
  friend class ListIterator<T>;
  friend ostream &operator<<(ostream &os, const List<double> &list);
};

ostream &operator<<(ostream &os, const List<double> &list) {
  Node<double> *tmp = list.head;
  for (tmp = list.head; tmp; tmp = tmp->next) {
    os << tmp->data << " ";
  }
  return os;
}

template <class T>
class ListIterator : public iterator<forward_iterator_tag, T>{
public:
  ListIterator() { cur = NULL; }
  ListIterator(Node<T> *cur_) { cur = cur_; }
  ListIterator(const ListIterator &it) { cur = it.cur; }
  ListIterator &operator=(const ListIterator &it) { cur = it.cur; return *this; }
  bool operator==(const ListIterator &it) const { return cur == it.cur; }
  bool operator!=(const ListIterator &it) const { return cur != it.cur; }
  ListIterator operator++() { cur = cur->next; return *this; }
  ListIterator operator++(int) {
    ListIterator<T> tmp(cur);
    cur = cur->next;
    return tmp;
  } /* postincrement it++ */
  T &operator*() { return cur->data; }
private:
  Node<T> *cur;
};

int main() {
  List<double> dl;
  List<double> dl2;
  List<int> il;
  ListIterator<double> di;
  dl.insert_head(3.2);
  dl.insert_head(5.4);
  for (di=dl.begin(); di!=dl.end(); di++)
    cout << *di << endl;
  dl2 = dl;
  di=dl.begin();
  *di = 1.5;
  for (auto di2: dl2)
    cout << di2 << endl;
  dl = dl2;
  cout << dl << endl;
  il.insert_head(5);
  il.insert_head(7);
  for (auto it: il)
    cout << it << endl;
  return 0;
}
