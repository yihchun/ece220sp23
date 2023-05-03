#include <iostream>

using namespace std;
class foo {
public:
  ~foo() { cout << "destroying foo w z=" << z << endl; }
  virtual foo test(int x) { z = x; return *this; }
protected:
  int z;
};

class bar : public foo {
public:
  ~bar() { cout << "destroying bar w z=" << z << endl; }
  template <class T>
  foo test(T x) { z = 0; return *this; }
  foo test(int x) { z = 2*x; return *this; }
};

int main() {
  bar baz;
  foo *foobar = &baz;
  foobar->test(3);
  baz.test("yay");
  baz.test(6);
}
