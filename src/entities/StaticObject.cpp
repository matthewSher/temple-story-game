#include "../../include/entities/StaticObject.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

StaticObject::StaticObject(sf::Vector2f p, sf::Sprite s) : Entity(p, s) {}

void StaticObject::interact() {
    // Реализация взаимодействия с объектом
    // Например, можно вывести сообщение в консоль или изменить состояние объекта
    std::cout << "Interacting with static object at position: " << position.x << ", " << position.y << std::endl;
} 
