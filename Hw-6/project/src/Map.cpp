#include <fstream>
#include <iostream>
#include "Map.h"
#include "Exeptions.h"

Map::Map(const std::string& mapPath) {
    std::ifstream is;
    is.exceptions(std::ifstream::goodbit | std::ifstream::badbit);

    try {
        is.open(mapPath);
        is >> rowsSize >> colsSize;

        enemyMap.resize(rowsSize, std::vector<Enemy>(colsSize));
        clothesMap.resize(rowsSize, std::vector<Clothes>(colsSize));
        ClothesFactory& clothesFactory = ClothesFactory::GetInstance();
        EnemyFactory& enemyFactory = EnemyFactory::GetInstance();

        while (!is.eof()) {
            size_t x = 0;
            size_t y = 0;
            std::string name;

            is >> x >> y >> name;

            if (!name.empty()) {
                clothesMap[x][y] = clothesFactory.GetClothes(name);
                enemyMap[x][y] = enemyFactory.GetEnemy(name);
            }
        }
    } catch (const std::ifstream::failure&) {
        throw InvalidFileOperation();
    }
}

Enemy& Map::GetEnemy(const size_t x, const size_t y) {
    return enemyMap[x][y];
}

Clothes& Map::GetClothes(size_t x, size_t y) {
    return clothesMap[x][y];
}

void Map::SetClothesEmpty(size_t x, size_t y) {
    clothesMap[x][y].SetEmpty();
}

int Map::GetPossibleActions(Player &player, Stage& stage) const {
    bool isSelected = false;

    std::cout << "Supported actions:" << std::endl;

    if (player.IsFighting()) {
        std::cout << " * kick enemy" << std::endl;
        isSelected = true;

    } else {
        if (GetPossibleMoves(player) == 0) {
            isSelected = true;
        }

        if (player.IsTaking() && stage == PLUSCLOTHESGAME && GetPossibleClothes(player) == 0) {
            isSelected = true;
        }

        if (!isSelected) {
            std::cout << std::endl;
        }
    }

    if (stage == PLUSCLOTHESGAME) {
        std::cout << player.GetXPosition() << " x " << player.GetYPosition() << ", hp: " << player.GetPlayerHp() << ", armor: " << player.GetPlayerArm() << " > ";
    } else {
        std::cout << player.GetXPosition() << " x " << player.GetYPosition() << ", hp: " << player.GetPlayerHp() << " > ";
    }

    if (!isSelected) {
        return -1;
    }

    return 0;
}

int Map::GetPossibleMoves(Player &player) const {
    bool isSelected = false;

    if (player.GetXPosition() != 0) {
        std::cout << " * move left" << std::endl;
        isSelected = true;
    }

    if (player.GetXPosition() != rowsSize - 1) {
        std::cout << " * move right" << std::endl;
        isSelected = true;
    }

    if (player.GetYPosition() != 0) {
        std::cout << " * move down" << std::endl;
        isSelected = true;
    }

    if (player.GetYPosition() != colsSize - 1) {
        std::cout << " * move up" << std::endl;
        isSelected = true;
    }

    if (!isSelected) {
        return -1;
    }

    return 0;
}

int Map::GetPossibleClothes(Player &player) const {
    bool isSelected = false;

    if (player.IsTaking()) {
        auto clothes = clothesMap[player.GetXPosition()][player.GetYPosition()];
        bool isSimple = false;

        for (size_t i = 0; i < player.GetClothesSize(); i++) {
            if (clothes.GetClothesName() == player.GetClothes(i).GetClothesName()) {
                isSimple = true;
            }
        }

        if (!isSimple) {
            std::cout << " * pick " << clothesMap[player.GetXPosition()][player.GetYPosition()].GetClothesName() << std::endl;
            isSimple = true;
        }
    }

    for (size_t i = 0; i < player.GetClothesSize(); i++) {
        if (!player.GetClothes(i).GetClothesName().empty()) {
            std::cout << " * throw " << player.GetClothes(i).GetClothesName() << std::endl;
            isSelected = true;
        }
    }

    if (!isSelected) {
        return -1;
    }

    return 0;
}
