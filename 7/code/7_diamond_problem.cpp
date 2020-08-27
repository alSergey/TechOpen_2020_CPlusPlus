#include <iostream>

// Base  foo
// /     \
// L foo  R foo
//  \    /
//     C::foo

class Base {
 public:
  Base(int i)
      : m_i(i) {
    std::cout << "ctr Base " << i << std::endl;
  }

  ~Base() {
    std::cout << "dtr Base " << m_i << std::endl;
  }

  virtual
  void foo(int v) {
    std::cout << "foo_Base " << m_i * v << std::endl;
  }

 private:
  int m_i;
};

class Left : virtual public Base {
 public:
  Left(int i, int j)
      : Base(i)
      , m_j(j) {
    std::cout << "ctr Left " << j << std::endl;
  }

  ~Left() {
    std::cout << "dtr Left " << m_j << std::endl;
  }

 private:
  int m_j;
};

class Right : virtual public Base {
 public:
  Right(int i, int j)
      : Base(i)
      , m_j(j) {
    std::cout << "ctr Right " << j << std::endl;
  }

  ~Right() {
    std::cout << "dtr Right " << m_j << std::endl;
  }

  void foo(int v) override {
    Base::foo(v);
    std::cout << "foo_Right " << m_j * v << std::endl;
  }

 private:
  int m_j;
};

class Result : public Left, public Right {
 public:
  Result(int i, int j)
      : Base(0)
      , Left(i, j)
      , Right(2 * i, 2 * j) {
    std::cout << "ctr Result " << std::endl;
  }

  ~Result() {
    std::cout << "dtr Result " << std::endl;
  }

//  void foo(int v) override {
//  }
};

//B L R Res
int main() {
  Result result(1, 2);
  result.Left::foo(324);
  return 0;
}