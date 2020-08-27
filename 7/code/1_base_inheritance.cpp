#include <iostream>

class A {
 public:
  A(int i = 0)
      : m_i(i) {
    std::cout << this << "  A(" << m_i << ")" << std::endl;
  }

  A(const A& rhs) {
    std::cout << this << "  A(const A&) m_i=" << m_i << " rhs=" << &rhs << std::endl;
  }

  ~A() {
    std::cout << this << " ~A(" << m_i << ")" << std::endl;
  }

 private:
  int m_i;
};

class B : public A {
 public:
  B(int i)
      : m_i(i) {
    std::cout << this << "  B(" << m_i << ")" << std::endl;
  }

  B(const B& rhs) {
    std::cout << this << "  B(const B&) m_i=" << m_i << " rhs=" << &rhs << std::endl;
  }

  ~B() {
    std::cout << this << " ~B(" << m_i << ")" << std::endl;
  }

 private:
  int m_i;
};

class C : public B {
 public:
  C(int i = 0)
      : B(i + 2)
      , m_i(i) {
    std::cout << this << "  C(" << m_i << ")" << std::endl;
  }

  C(const C& rhs): B(rhs) {
    std::cout << this << "  C(const C&) m_i=" << m_i << " rhs=" << &rhs << std::endl;
  }

  ~C() {
    std::cout << this << " ~C(" << m_i << ")" << std::endl;
  }

 private:
  int m_i;
};


int main() {
  C c;

  return 0;
}