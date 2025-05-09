#pragma once

#include <SFML/Graphics.hpp>
#include "../StaticObject.hpp"

/**
 * Класс Letter - письмо, которое можно прочесть.
 */
class Letter : public StaticObject {
private:
    std::string text;
public:
    Letter(sf::Vector2f p, sf::Sprite s, const std::string& text);

    void interact() override;
};