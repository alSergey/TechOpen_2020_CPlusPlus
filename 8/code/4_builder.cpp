#include <vector>
#include <string>
#include <iostream>
#include <sstream>

//enum FoodType {
//};
//
//class Pizza {
//};
//
//class PizzaBuilder {
// public:
//  PizzaBuilder& add_food(FoodType, int);
//
//  Pizza get_pizza();
//};
//
//PizzaBuilder pb;
//Pizza p = pb
//    .add_food(pp, 20)
//    .add_food(a, 100)
//    .add_food(ch, 500)
//    .get_pizza()

class StringBuilder {
 public:
  StringBuilder& operator<<(const std::string& str) {
    for (auto& ch: str) {
      m_buf.push_back(ch);
    }
    return *this;
  }

  std::string get_string() {
    return std::string(m_buf.data());
  }

 private:
  std::vector<char> m_buf;
};

int main() {
  std::string sum_str =
      std::string("Hello,") + std::string(" ") + std::string("world");

  StringBuilder builder;
//  builder << "Hello" << ", " << "world";

//  for (int i = 0; i < 3; ++i) {
//    std::string str;
//    std::cin >> str;
//    builder << str;
//  }

//  std::string builder_str = builder.get_string();

//  std::cout << builder_str;

  std::stringstream ss;
  ss << "Hello" << ", " << "world";
  std::cout << ss.str() << std::endl;

  return 0;
}