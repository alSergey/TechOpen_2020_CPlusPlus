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
  void foo() {
    std::cout << "foo A" << std::endl;
  }

 private:
  int m_i;
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
  void foo() {
    std::cout << "foo B" << std::endl;
  }

 private:
  int m_i;
};

A* foo(A* a) {
//  return A(42);
  return new A(43);
}

void bar(A a) {
  (void)a;
}


int main() {
//  A obj = A(42);
//  A* obj_ptr = new A(43);
//  delete obj_ptr;

//  A arr[5] = {A(1), A(2), A(3)};
//  for (auto& ptr : arr) {
//    ptr.foo();
//  }

//  A* arr_dyn = new A[5];
//  arr_dyn[1] = A(5);
//  delete[] arr_dyn;

//  A* ptr = new B(1234);
//  delete ptr;

//  auto* ptr_t = new int(123);
//  auto* arr_t = new int[46];
//
//  A* arr_poly[3] = {new A, new B, new B(123)};
//  for (auto& ptr: arr_poly) {
//    ptr->foo();
//  }

  return 0;
}