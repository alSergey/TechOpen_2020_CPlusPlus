#include "Game.h"
#include <iostream>

Game &Game::GetInstance() {
    static Game instance;
    return instance;
}

void Game::Run(const std::string &mapPath, Stage& stage) {
    Map map(mapPath);

    Player player;

    while (true) {
        if (map.GetPossibleActions(player, stage) == -1) {
            break;
        }

        std::string action;
        std::getline(std::cin, action);

        if (player.IsFighting()) {
            if (action == "kick enemy" && PlayerFight(player, map) == -1) {
                break;
            }

        } else {
            if (PlayerAction(action, player, map, stage) == -1) {
                break;
            }
        }
    }
}

int Game::PlayerAction(const std::string &action, Player &player, Map &map, Stage& stage) {
    if (stage == PLUSCLOTHESGAME) {
        std::string throwAction = action.substr(0, 5);
        if (throwAction == "throw") {
            PlayerThrow(action, player);
            return 0;
        }

        if (player.IsTaking() && PlayerPick(action, player, map) == 0) {
            return 0;
        }
    }

    if (PlayerMove(action, player, map) == 0) {
        return 0;
    }

    return -1;
}

int Game::PlayerMove(const std::string &action, Player &player, Map &map) {
    bool isSelected = true;

    if (action == "move left" && isSelected) {
        player.Move(-1, 0);
        isSelected = false;
    }

    if (action == "move right" && isSelected) {
        player.Move(1, 0);
        isSelected = false;
    }

    if (action == "move down" && isSelected) {
        player.Move(0, -1);
        isSelected = false;
    }

    if (action == "move up" && isSelected) {
        player.Move(0, +1);
        isSelected = false;
    }

    if (isSelected) {
        return -1;
    }

    if (CheckPlayerState(player, map) == -1) {
        return 0;
    }

    std::cout << std::endl << "moved" << std::endl;

    return 0;
}

int Game::CheckPlayerState(Player &player, Map &map) {
    auto posEnemy = map.GetEnemy(player.GetXPosition(), player.GetYPosition());
    if (!posEnemy.GetName().empty()) {
        std::cout << std::endl << posEnemy.GetName() << " found, " << posEnemy.GetHp() << " hp" << std::endl;
        player.Fighting(true);
        return -1;
    }

    auto posClothes = map.GetClothes(player.GetXPosition(), player.GetYPosition());
    if (!posClothes.GetClothesName().empty()) {
        std::cout << std::endl << posClothes.GetClothesName() << " found" << std::endl;
        player.Taking(true);
        return -1;
    }

    return 0;
}

int Game::PlayerPick(const std::string &action, Player &player, Map &map) {
    std::string clothesName = action.substr(5);
    ClothesFactory& clothesFactory = ClothesFactory::GetInstance();
    auto newClothes = clothesFactory.GetClothes(clothesName);

    map.SetClothesEmpty(player.GetXPosition(), player.GetYPosition());
    player.Taking(false);

    if (!newClothes.GetClothesName().empty()) {
        if (player.PickClothes(newClothes) == -1) {
            return -1;
        }

        std::cout << std::endl << "clothes worn" << std::endl;
        return 0;
    }

    return -1;
}

void Game::PlayerThrow(const std::string &action, Player &player) {
    std::string clothesName = action.substr(6);
    ClothesFactory& ClothesFactory = ClothesFactory::GetInstance();
    auto throwClothes = ClothesFactory.GetClothes(clothesName);
    player.ThrowClothes(throwClothes);
    std::cout << std::endl << "the " << throwClothes.GetClothesName() << " is thrown out" << std::endl;
}

int Game::PlayerFight(Player &player, Map &map) {
    auto& fightEnemy = map.GetEnemy(player.GetXPosition(), player.GetYPosition());
    if (Fight(player, fightEnemy)) {
        std::cout << std::endl << "enemy killed" << std::endl;
        player.Fighting(false);
        fightEnemy.SetValues("", 0, 0);
        return 0;
    }

    if (Fight(fightEnemy, player)) {
        std::cout << std::endl << "player died" << std::endl;
        return -1;
    }

    std::cout << std::endl << "enemy kicked." << " Enemy hp: " << fightEnemy.GetHp() << std::endl;
    return 0;
}

bool Game::Fight(Fighter &fighter, Fighter &def) {
    return def.TakeHit(fighter.PutDmg());
}
