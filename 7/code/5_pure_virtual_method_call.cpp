#include <iostream>

class A {
 public:
  A() {
    pure_virtual();
    foo();
  }

  void foo() {
    pure_virtual();
  }

  virtual
  void pure_virtual() = 0;
};


class B: public A {
 public:
  void pure_virtual() override {
  }
};


int main() {
  B b;
  return 0;
}