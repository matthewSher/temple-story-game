#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

class GameState {
public:
    virtual void handleInput(const sf::Event::KeyPressed *keyEvent) = 0;
    virtual void render(sf::RenderWindow& window) = 0;

    virtual ~GameState() = default;
};