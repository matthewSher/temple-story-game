#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.hpp"

class Character : public Entity {
protected:
    int maxHealth;
    int currentHealth;
    float speed;
    sf::Vector2f direction;
    bool isMoving;

public:
    Character(sf::Vector2f p, sf::Sprite s, int h, float spd);
    virtual ~Character() = default;

    void move(sf::Vector2f dir);
    void takeDamage(int amount);
    void heal(int amount);
    bool isDead() const;
    float getSpeed() const;
    sf::Vector2f getPosition() const override;
};