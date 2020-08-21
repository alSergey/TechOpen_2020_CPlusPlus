#pragma once

#include "Enemy.h"
#include "Player.h"
#include "Clothes.h"
#include "EnemyFactory.h"
#include "ClothesFactory.h"
#include <iosfwd>
#include <string>
#include <vector>

enum Stage {STANDARTGAME, PLUSCLOTHESGAME};

class Map {
 public:
    explicit Map(const std::string& mapPath);
    ~Map() = default;
    Enemy& GetEnemy(size_t x, size_t y);
    Clothes& GetClothes(size_t x, size_t y);
    void SetClothesEmpty(size_t x, size_t y);
    int GetPossibleActions(Player& player, Stage& stage) const;
 private:
    size_t rowsSize{};
    size_t colsSize{};
    std::vector<std::vector<Enemy>> enemyMap;
    std::vector<std::vector<Clothes>> clothesMap;
    int GetPossibleMoves(Player& player) const;
    int GetPossibleClothes(Player& player) const;
};
