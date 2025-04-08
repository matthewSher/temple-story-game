#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.hpp"

/**
 * Класс Character представляет собой игрового персонажа.
 * Он наследуется от класса Entity и добавляет функциональность
 * для управления состоянием персонажа, его движением и взаимодействием с окружающим миром.
 */
class Character : public Entity {
protected:
    int maxHealth;          // Максимальное здоровье персонажа
    int currentHealth;      // Текущее здоровье персонажа
    float speed;            // Скорость движения персонажа

public:
    Character(sf::Vector2f p, sf::Sprite s, int h, float spd);
    virtual ~Character() = default;

    // Перемещение персонажа в заданном направлении
    // dir - вектор направления перемещения (например, (1, 0) для движения вправо)
    void move(sf::Vector2f dir);
    // Персонаж получает урон
    void takeDamage(int amount);
    // Персонаж восстанавливает здоровье
    void heal(int amount);
    // Проверка, мертв ли персонаж
    bool isDead() const;
    // Получение скорости персонажа
    float getSpeed() const;
    // Получение позиции персонажа в виде вектора (x, y)
    // Позиция возвращается в координатах тайлов (например, (1, 2) для тайла в позиции (32, 64))
    sf::Vector2f getPosition() const override;
};