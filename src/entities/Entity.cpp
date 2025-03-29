#include "../../include/entities/Entity.hpp"

Entity::Entity(sf::Vector2f p, sf::Sprite s) : position(p), sprite(s) {
    sprite.setPosition(p);
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}