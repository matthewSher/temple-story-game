#pragma once

#include "Entity.hpp"

/**
 * Класс StaticObject представляет собой статический объект в игре.
 * Он наследуется от класса Entity и добавляет функциональность взаимодействия с объектом.
 */
class StaticObject : public Entity {
public:
    StaticObject(sf::Vector2f p, sf::Sprite s);

    // Метод для взаимодействия с объектом
    void interact();
};
