//
// Created by tsv on 18.04.19.
//

#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H


#include <SFML/System/Vector2.hpp>
#include "GameObject.h"

const float PLAYER_VELOCITY = 10.0f;

class Player : public GameObject {
public:
    explicit Player(const sf::Vector2f& position = sf::Vector2f{10.0f, 10.0f});

    void update(float dt) override;

    const sf::Vector2f get_position() const;

private:
    sf::Vector2f m_position;
    sf::Vector2f m_direction;
    float m_velocity;
};

using PlayerPtr = std::shared_ptr<Player>;

#endif //GAME_PLAYER_H
