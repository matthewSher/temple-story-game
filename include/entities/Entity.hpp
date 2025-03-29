#pragma once

#include <SFML/Graphics.hpp>

class Entity : public sf::Drawable {
protected:
    sf::Vector2f position;
    sf::Sprite sprite;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    Entity(sf::Vector2f p, sf::Sprite s);
    virtual ~Entity() = default;
};

