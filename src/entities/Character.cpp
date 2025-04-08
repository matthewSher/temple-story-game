#include "../../include/entities/Character.hpp"

#include "../../include/constants/main_constants.h"

Character::Character(sf::Vector2f p, sf::Sprite s, int h, float spd)
    : Entity(p, s), currentHealth(h), maxHealth(h), speed(spd) {}

void Character::move(sf::Vector2f dir) {
    position += dir * speed;
    sprite.setPosition(position);
}

void Character::takeDamage(int amount) {
    currentHealth -= amount;
    if (currentHealth < 0) currentHealth = 0;
}

void Character::heal(int amount) {
    currentHealth += amount;
    if (currentHealth > maxHealth) currentHealth = maxHealth;
}

bool Character::isDead() const {
    return currentHealth == 0;
}

float Character::getSpeed() const {
    return speed;
}

sf::Vector2f Character::getPosition() const {
    return {position.x / TILE_SIZE, position.y / TILE_SIZE};
}