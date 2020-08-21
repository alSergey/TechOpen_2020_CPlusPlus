#include "Game.h"
#include <iostream>

int main(int argc, char *argv[]) {
    if (argc < 3 && argc > 4) {
        return -1;
    }

    std::string key;
    std::string mapPath;
    std::string stage2;
    Stage stage = STANDARTGAME;

    for (int num = 0; num < argc; ++num) {
        std::string str = argv[num];
        if (str == "--map") {
            key = str;
        }

        if (str == "--view-armor") {
            stage2 = str;
            stage = PLUSCLOTHESGAME;
        }

        if (str != "--view-armor" && str != "--map") {
            mapPath = str;
        }
    }

    Game& game = Game::GetInstance();
    game.Run(mapPath, stage);

    return 0;
}
