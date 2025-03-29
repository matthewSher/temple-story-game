#pragma once

#include "Character.hpp"

class Player : public Character {
public:
    Player(sf::Vector2f p, sf::Sprite& s, int h, float spd);

    virtual void update(float dt) override;
};