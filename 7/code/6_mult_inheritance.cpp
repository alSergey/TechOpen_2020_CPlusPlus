#include <iostream>

class Cat {
 public:
  virtual
  void sound() {
    std::cout << "Meow" << std::endl;
  }

  void ignore_you() {
    std::cout << "zZzZzZzZ" << std::endl;
  }

  int hp;
};

class Dog {
 public:
  virtual
  void sound() {
    std::cout << "Woof" << std::endl;
  }

  void good_boy() {
    std::cout << "Awwwwwww" << std::endl;
  }
  int hp;
};


class CatDog: public Cat, public Dog {
 public:
//  void sound() override {
//    Cat::sound();
//    Dog::sound();
//  }
};

void use_cat(Cat& cat) {
  cat.sound();
  cat.ignore_you();
}

void use_dog(Dog& dog) {
  dog.sound();
  dog.good_boy();
}

// Cat    Dog
//   \    /
//   CatDog

int main() {
  CatDog cat_dog;
  cat_dog.sound();
  use_cat(cat_dog);
  use_dog(cat_dog);

  std::cout << cat_dog.Dog::hp;
  return 0;
}