//
// Created by tsv on 18.04.19.
//

#include "Object.h"

Object::Object(uint id, const sf::Vector2f& position)
        : m_id(id)
        , m_position(position) {
}

void Object::set_position(const sf::Vector2f& position) {
    m_position = position;
}
