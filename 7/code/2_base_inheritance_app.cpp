#include <iostream>

class Potion {
 public:
  explicit Potion(int volume = 0)
      : m_volume(volume) {
  }

  void drink() {
    if (m_volume) {
      --m_volume;
    }
    do_drink();
  }

  virtual
  void do_drink() = 0;

  void drink_full() {
    while (get_volume()) {
      drink();
      std::cout << get_volume() << std::endl;
    }
  }

  void refill(int volume) {
    m_volume += volume;
  }

  int get_volume() const {
    return m_volume;
  }

 private:
  int m_volume;
};

class HP : public Potion {
 public:
  HP() = default;

  HP(int volume, int power)
      : Potion(volume)
      , m_power(power) {
  }

  void do_drink() override {
    std::cout << "Restore " << m_power << " hp" << std::endl;
  }

  int get_power() const {
    return m_power;
  }

 private:
  int m_power;
};

class Mana : public HP {
 public:
  Mana(int vol, int power)
      : HP(vol, power) {
  }

  void do_drink() override {
    std::cout << "Restore " << get_power() << " mana" << std::endl;
  }
};

int main() {
  HP hp1;

  HP hp(5, 17);
  hp.drink_full();

  Mana mana(3, 1234);
  mana.drink_full();

  return 0;
}