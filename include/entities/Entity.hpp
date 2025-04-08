#pragma once

#include <SFML/Graphics.hpp>

/**
 * Базовый класс для всех игровых объектов. 
 * Содержит общие методы и свойства для всех объектов,
 * которые будут отображаться на экране.
 * Наследуется от класса sf::Drawable для возможности 
 * отрисовки библиотекой SFML.
 */
class Entity : public sf::Drawable {
protected:
    // Позиция объекта в пикселях
    sf::Vector2f position;
    // Спрайт объекта используется для отрисовки объекта на экране
    sf::Sprite sprite;

    // Метод отрисовки объекта на экране
    // Переопределяет метод draw из класса sf::Drawable
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    Entity(sf::Vector2f p, sf::Sprite s);
    virtual ~Entity() = default;

    // Получить позицию объекта в пикселях
    virtual sf::Vector2f getPosition() const;
};

