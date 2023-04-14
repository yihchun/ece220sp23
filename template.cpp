#include <iostream>

using namespace std;

template <class Typea, class Typeb>
Typea sum(Typea a, Typeb b) {
  return a+b;
}

int main() {
  int x;
  void *y = &x;
  void *z = &x;
  cout << sum(3,5) << endl;
  cout << sum(3.2,5.7) << endl;
  cout << sum(3.2,5) << endl;
  cout << sum(5,3.2) << endl;
  return 0;
}
