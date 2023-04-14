#include <iostream>

using namespace std;

class Foo {
  int z;
public:
  virtual void identify() const { cout << "I am a Foo\n"; }
  virtual void onlyforfoo() const { cout << "Hi there\n"; }
};

class Bar : public Foo {
public:
  void identify() const { cout << "I am a Bar\n"; }
  void onlyforfoo() const { cout << "This is Bar\n"; }
};

class Baz : public Bar {
public:
  void identify() const { cout << "I am a Baz\n"; }
  void onlyforfoo() const { cout << "This is Baz\n"; }
};

/* double check if virtual-ness is inherited by derived classes */

int main() {
  Foo *x;
  Bar *b;
  Baz z;
  x = &z;
  b = &z;
  x->identify();
  b->identify();
  return 0;
}
