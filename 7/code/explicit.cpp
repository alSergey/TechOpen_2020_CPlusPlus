#include <iostream>
#include <fstream>

class A {
 public:
  explicit A(int i) {
  }

  void foo() {
    std::cout << "foo A";
  }

  explicit operator bool() {
    return true;
  }
};

void bar(A a) {
  a.foo();
}

void read(std::istream& is){
  std::string str1;
  std::string str2;
  int i;
  double d;

  is >> str1 >> str2 >> i >> d;
  std::cout << str1 << ' ' << str2 << i << d;
}
int main() {
  read(std::cin);

  std::ifstream ifs("test.txt");
  read(ifs);

  return 0;
}