#include <iostream>

class A {
 public:
  A(int i = 1337)
      : m_i(i) {
    std::cout << this << "  A(" << m_i << ")" << std::endl;
  }

  A(const A& rhs) {
    std::cout << this << "  A(const A&) m_i=" << m_i << " rhs=" << &rhs << std::endl;
  }

  ~A() {
    std::cout << this << " ~A(" << m_i << ")" << std::endl;
  }

  virtual
  void foo(int v) const {
    std::cout << this << " foo_A " << v << std::endl;
  }

  void non_virtual() const {
    std::cout << this << " non_virtual_A " << std::endl;
  }

 private:
  int m_i;
  // vt* pvt;
};

class B : public A {
 public:
  B(int i = 789)
      : A(i + 1)
      , m_i(i) {
    std::cout << this << "  B(" << m_i << ")" << std::endl;
  }

  B(const B& rhs) {
    std::cout << this << "  B(const B&) m_i=" << m_i << " rhs=" << &rhs << std::endl;
  }

  ~B() {
    std::cout << this << " ~B(" << m_i << ")" << std::endl;
  }

  virtual
  void foo(int v) const override {
    std::cout << "foo_B " << v << std::endl;
  }

  void non_virtual() const {
    std::cout << "non_virtual_B " << std::endl;
  }

 private:
  int m_i;
};

class C : public B {
 public:
  C(int i = 42)
      : m_i(i) {
    std::cout << this << "  C(" << m_i << ")" << std::endl;
  }

  C(const C& rhs) {
    std::cout << this << "  C(const C&) m_i=" << m_i << " rhs=" << &rhs << std::endl;
  }

  ~C() {
    std::cout << this << " ~C(" << m_i << ")" << std::endl;
  }

 private:
  int m_i;
};

void bar(const A& a) {
  std::cout << "bar ref ";
  a.foo(1399);
  a.non_virtual();
}

void bar(const A* a) {
  std::cout << "bar pointer ";
  a->foo(2007);
  a->non_virtual();
}

//void bar(A a){
//  a.foo(5553535);
//  a.non_virtual();
//}

//typedef int MYINT;
//using MYINT1 = int;
//
//typedef int (*p_foo)(int, float*);
using p_foo = void (*)();


void foo1(){
  std::cout << "foo1" << std::endl;
}

void foo2(){
  std::cout << "foo2" << std::endl;
}

void spam(p_foo vt[1]){
  vt[0]();
}
int main() {

  p_foo vtable1[1] = {foo1};
  p_foo vtable2[1] = {foo2};

  spam(vtable1);
  spam(vtable2);

  C c;
  bar(c);


  return 0;
}