#include <stdio.h>

struct twodvec {
  float x, y;
};

struct twodvec add(struct twodvec a, struct twodvec b) {
  struct twodvec ret;
  ret.x = a.x + b.x;
  ret.y = a.y + b.y;
  return ret;
}


