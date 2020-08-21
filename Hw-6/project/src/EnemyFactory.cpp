#include "EnemyFactory.h"

EnemyFactory &EnemyFactory::GetInstance() {
    static EnemyFactory instance;
    instance.enemyKeyMap.insert(std::make_pair("wolf", std::function<Enemy()>(GetWolf)));
    instance.enemyKeyMap.insert(std::make_pair("dog",   std::function<Enemy()>(GetDog)));
    instance.enemyKeyMap.insert(std::make_pair("rat", std::function<Enemy()>(GetRat)));
    return instance;
}

Enemy EnemyFactory::GetEnemy(const std::string& name) {
        if (enemyKeyMap.find(name) == enemyKeyMap.end()) {
        return Enemy("", 0, 0);
    }

    return enemyKeyMap[name]();
}

Enemy EnemyFactory::GetWolf() {
    return Enemy("wolf", 6, 11);
}

Enemy EnemyFactory::GetDog() {
    return Enemy("dog", 3, 6);
}

Enemy EnemyFactory::GetRat() {
    return Enemy("rat", 2, 4);
}
