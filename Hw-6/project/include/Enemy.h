#pragma once

#include "Fighter.h"
#include <string>

class Enemy: public Fighter {
 public:
    explicit Enemy(std::string name = "", int hp = 0, int dmg = 0);
    ~Enemy() override = default;
    bool TakeHit(int dmg) override;
    int PutDmg() override;
    void SetValues(std::string name, int hp, int dmg);
    std::string GetName() const;
    int GetHp() const;
 private:
    std::string enemyName;
    int enemyHp;
    int enemyDmg;
};
