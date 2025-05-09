#include "../../include/entities/StaticObject.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

StaticObject::StaticObject(sf::Vector2f p, sf::Sprite s) : Entity(p, s) {}
