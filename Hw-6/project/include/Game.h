#pragma once

#include "Player.h"
#include "Map.h"
#include "Fighter.h"
#include "Clothes.h"
#include "ClothesFactory.h"
#include <string>

class Game {
 public:
    static void Run(const std::string& mapPath, Stage& stage);
    static Game& GetInstance();
 private:
    Game() = default;
    ~Game() = default;
    Game(const Game&);
    Game& operator=(const Game&);
    static int PlayerAction(const std::string& action, Player& player, Map& map, Stage& stage);
    static int PlayerMove(const std::string& action, Player& player, Map& map);
    static int CheckPlayerState(Player& player, Map& map);
    static int PlayerPick(const std::string& action, Player& player, Map& map);
    static void PlayerThrow(const std::string& action, Player& player);
    static int PlayerFight(Player& player, Map& map);
    static bool Fight(Fighter& fighter, Fighter& def);
};
