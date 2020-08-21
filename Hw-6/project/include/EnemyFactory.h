#pragma once

#include "Enemy.h"
#include <functional>
#include <string>
#include <map>

class EnemyFactory {
 public:
    Enemy GetEnemy(const std::string& name);
    static EnemyFactory& GetInstance();
 private:
    EnemyFactory() = default;
    ~EnemyFactory() = default;
    EnemyFactory(const EnemyFactory&);
    EnemyFactory& operator=(const EnemyFactory&);
    static Enemy GetWolf();
    static Enemy GetDog();
    static Enemy GetRat();
    std::map<std::string, std::function<Enemy()>> enemyKeyMap;
};
