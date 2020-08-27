//
// Created by tsv on 18.04.19.
//

#include "Player.h"

Player::Player(uint id, const std::string& username, const sf::Vector2f& position)
        : Object(id, position)
        , m_username(username)
        , m_actor(10) {
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(m_actor);
}

void Player::set_position(const sf::Vector2f& position) {
    Object::set_position(position);
    m_actor.setPosition(m_position);
}
