#include <iostream>
using namespace std;
class twodvec {
  float x, y;
public:
  twodvec() { x = y = 0; }
  twodvec(float x_, float y_) { x = x_; y = y_; }
  ~twodvec() {
    cout << "I am being deallocated! " << this << endl;
  }
  twodvec add(twodvec b) {
    twodvec ret;
    ret.x = x + b.x;
    ret.y = y + b.y;
    return ret;
  }
  void print(ostream &os) {
    os << x << "," << y << endl;
  }
};

int main() {
  twodvec a(2,1);
  twodvec b(1,1);
  twodvec c = a.add(b);
  c.print(cout);
  return 0;
}

