#pragma once

#include <memory>

#include "../Game.hpp"

class Game;

class GameState {
public:
    virtual void handleInput(const sf::Event::KeyPressed *keyEvent) = 0;
    // virtual void update(float dt) = 0;
    virtual void render(sf::RenderWindow& window) = 0;

    virtual ~GameState() = default;
};