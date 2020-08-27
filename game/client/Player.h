//
// Created by tsv on 18.04.19.
//

#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H


#include "Object.h"

#include <SFML/Graphics/CircleShape.hpp>

#include <string>

class Player : public Object {
public:
    Player(uint id, const std::string& username, const sf::Vector2f& position);

    void draw(sf::RenderWindow& window) override;

    void set_position(const sf::Vector2f& position) override;

private:
    std::string m_username;
    sf::CircleShape m_actor;
};


#endif //GAME_PLAYER_H
