//
// Created by tsv on 18.04.19.
//

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H


#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <memory>

class Object {
public:
    explicit Object(uint id, const sf::Vector2f& position);

    virtual
    void set_position(const sf::Vector2f& position);

    virtual
    void draw(sf::RenderWindow& window) = 0;

protected:
    uint m_id;
    sf::Vector2f m_position;
};

using ObjectPtr = std::shared_ptr<Object>;

#endif //GAME_OBJECT_H
