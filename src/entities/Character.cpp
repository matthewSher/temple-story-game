#include "../../include/entities/Character.hpp"

Character::Character(sf::Vector2f p, sf::Sprite s, int h, float spd)
    : Entity(p, s), currentHealth(h), maxHealth(h), speed(spd), isMoving(false) {}

void Character::move(sf::Vector2f dir) {
    direction = dir;
    isMoving = true;
    position += direction * speed;
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