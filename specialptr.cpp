#include <iostream>

using namespace std;

class A {
public:
  A() { cout << this << " created by default constructor" << endl; }
  A(int x) { cout << this << " created by constructor " << x << endl; }
  ~A() { cout << this << " destructed" << endl; }
};

template <class T>
class uniqueptr {
  T *ptr;
public:
  uniqueptr() { ptr = new T; }
  template <typename ... Args>
  uniqueptr(Args && ... arg) { ptr = new T(std::forward<Args>(arg)...); }
  uniqueptr(const uniqueptr &x) = delete;
  ~uniqueptr() { delete ptr; }
  T &operator*() { return *ptr; }
  uniqueptr &operator=(const uniqueptr &x) = delete;
  /* move the current pointer into an existing uniqueptr x */
  void moveto(uniqueptr &x) {
    T *tmp = ptr;
    delete x.ptr;
    x.ptr = tmp;
    ptr = NULL;
  }
};

template <class T>
class shareptr {
  class controlblock {
  public:
    controlblock(T *p) { ptr = p; count = 1; }
    T *ptr;
    int count;
  };
  controlblock *ptr;
  void decrcount() {
    if (!ptr) return;
    cout << "Handling " << ptr->ptr << " count was " << ptr->count << endl;
    ptr->count--;
    if (!ptr->count) {
      delete ptr->ptr;
      delete ptr;
    }
  }
public: 
  shareptr() { ptr = new controlblock(new T); }
  ~shareptr() { decrcount(); }
  shareptr(const shareptr &x) {
    ptr = x.ptr;
    ptr->count++;
  }
  shareptr &operator=(const shareptr &x) {
    decrcount();
    ptr = x.ptr;
    ptr->count++;
    return *this;
  }
};
  
int main() {
  shareptr<A> x;
  shareptr<A> y;
  x = y;
}
