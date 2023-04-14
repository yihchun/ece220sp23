#include <iostream>
using namespace std;

class Rectangle {
  int width, height;
public:
  Rectangle();
  Rectangle(int, int);
  int area() { return width * height; }
};

Rectangle::Rectangle() {
  // set width, height to 0
  width = height = 0;
}

Rectangle::Rectangle(int a, int b) {
  // set width to a and height to b
  width = a;
  height = b;
}

int sum(int a, int b) {
  cout << "integer sum\n";
  return a+b;
}

float sum(float a, float b) {
  cout << "float sum\n";
  return a+b;
}

int main() {
  Rectangle rect1(3,4);
  Rectangle rect2;

  // print area of rect1
  cout << rect1.area() << endl;

  // print area of rect2
  cout << rect2.area() << endl;

  cout << sum(1,3) << endl;
  cout << sum(1.1f,3.2f) << endl;

  return 0;
}
