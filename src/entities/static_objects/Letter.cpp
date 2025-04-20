#include "../../../include/entities/static_objects/Letter.hpp"

#include <iostream>

Letter::Letter(sf::Vector2f p, sf::Sprite s) : StaticObject(p, s) {}

void Letter::interact() {
    // Реализация взаимодействия с объектом "Letter"
    // Например, вывод сообщения в консоль
    std::cout << "Вы подобрали письмо!" << std::endl;
}