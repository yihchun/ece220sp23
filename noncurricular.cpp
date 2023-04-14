#include <iostream>

using namespace std;

class Foo {
public:
  virtual void foofunc() { cout << "hi\n"; }
};

class Bar {
public:
  virtual void barfunc() { cout << "bar\n"; }
};

class Baz : public Foo, public Bar {
public:
  void foofunc() { cout << this << " hi there\n"; }
  void barfunc() { cout << this << " bar (actually baz)\n"; }
};

int main() {
  Baz z;
  Bar *b = &z;
  Foo *f = &z;
  f->foofunc();
  b->barfunc();
  cout << f << endl;
  cout << b << endl;
  return 0;
}

/* -> Baz Baz's foofunc Vft
          Baz's barfunc Vft <- 
*/

  
