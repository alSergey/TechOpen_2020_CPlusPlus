#include <iostream>

class A {
 public:
  virtual
  void abstr() = 0;

  virtual
  void virt() {
    std::cout << "virt_A " << std::endl;
  }

  void reg() {
    std::cout << "reg_A " << std::endl;
  }
};


class B : public A {
 public:
  void abstr() override {
    std::cout << "abstr_B " << std::endl;
  }

  void virt() override {
    A::virt();
    std::cout << "virt_B " << std::endl;
  }

  void reg() {
    std::cout << "reg_B " << std::endl;
  }

};


class C : public B {
 public:
  void abstr() override {
    std::cout << "abstr_C " << std::endl;
  }

  void spam_C() {
    std::cout << "spam C" << std::endl;
  }

};

class D : public C {
};

void bar(A& a) {
  a.abstr();
  a.virt();
  a.reg();

  C* pc = dynamic_cast<C*>(&a);
  if (pc != nullptr) {
    pc->spam_C();
  }
}

// A -> B -> C -> D

int main() {
//  A a;
  D d;
  bar(d);
  return 0;
}