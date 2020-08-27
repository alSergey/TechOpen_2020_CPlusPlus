#include <iostream>
#include <memory>


class Hittable {
 public:
  virtual
  bool take_hit(int dmg) = 0;
};

class Moveable {
 public:
  virtual
  void move(int distance) = 0;
};

class Damageable {
 public:
  virtual
  int get_damage() = 0;
};


class Tree : public Hittable {
 public:
  explicit Tree(int hp)
      : hp(hp) {
  }

  bool take_hit(int dmg) override {
    hp -= dmg;
    return hp > 0;
  }

 private:
  int hp;
};

class MagikTree: public Tree, public Damageable{

};

class NPC : public Moveable, public Damageable {
 public:
  NPC(int pos, int dmg)
      : pos(pos)
      , dmg(dmg) {
  }

  void move(int distance) override {
    pos += distance;
  }

  int get_damage() override {
    return 0;
  }

 private:
  int pos;
  int dmg;
};

class Player : public Moveable, public Damageable, public Hittable {
 public:
  Player(int pos, int armor)
      : pos(pos)
      , armor(armor) {
  }

  bool take_hit(int dmg) override {
    return armor >= dmg;
  }

  void move(int distance) override {
    pos += distance;
  }

  int get_damage() override {
    return 10;
  }

 private:
  int pos;
  int armor;
};

//std::shared_ptr<Damageable> == Damageable*
bool fight(std::shared_ptr<Damageable> attacker, std::shared_ptr<Hittable> defender) {
  return defender->take_hit(attacker->get_damage());
}

int main() {
  auto tree = std::make_shared<Tree>(5);
  auto npc = std::make_shared<NPC>(0, 100);
  auto player = std::make_shared<Player>(100, 3);

//  fight(tree, player);
//  fight(player, npc);

  std::cout << "Fight with tree" << std::endl;
  if (!fight(player, tree)) {
    std::cout << "Tree was cut" << std::endl;
    tree.reset();
  }
  std::cout << "battle end" << std::endl;

  std::cout << "Fight with npc" << std::endl;
  if (!fight(npc, player)) {
    std::cout << "You died" << std::endl;
    player.reset();
  }
  std::cout << "battle end" << std::endl;

  return 0;
}