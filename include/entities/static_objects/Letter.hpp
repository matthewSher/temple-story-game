#pragma once

#include <SFML/Graphics.hpp>
#include "../StaticObject.hpp"

class Letter : public StaticObject {
public:
    Letter(sf::Vector2f p, sf::Sprite s);

    void interact() override;
};