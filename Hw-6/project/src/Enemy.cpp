#include "Enemy.h"
#include <utility>

Enemy::Enemy(std::string name, int hp, int dmg)
    : enemyName(std::move(name))
    , enemyHp(hp)
    , enemyDmg(dmg) {
}

bool Enemy::TakeHit(int getDmg) {
    enemyHp -= getDmg;

    return enemyHp <= 0;
}

int Enemy::PutDmg() {
    return enemyDmg;
}

void Enemy::SetValues(std::string name, int hp, int dmg) {
    enemyName = std::move(name);
    enemyHp = hp;
    enemyDmg = dmg;
}

std::string Enemy::GetName() const {
    return enemyName;
}

int Enemy::GetHp() const {
    return enemyHp;
}
