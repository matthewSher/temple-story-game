#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <functional>

/**
 * Базовый класс для всех UI элементов
 * Предоставляет общий интерфейс для отрисовки и обработки событий
 */
class UIElement {
protected:
    sf::Vector2f position;
    sf::Vector2f size;
    bool isVisible = true;
    bool isActive = true;

public:
    UIElement(const sf::Vector2f& pos, const sf::Vector2f& size);
    virtual ~UIElement() = default;

    // Отрисовка элемента
    virtual void render(sf::RenderWindow& window) = 0;
    
    // Обработка событий
    virtual void handleEvent(const sf::Event& event) = 0;
    
    // Проверка, находится ли точка внутри элемента
    virtual bool contains(const sf::Vector2f& point) const;

    // Геттеры и сеттеры
    void setPosition(const sf::Vector2f& pos);
    void setSize(const sf::Vector2f& newSize);
    void setVisible(bool visible);
    void setActive(bool active);

    const sf::Vector2f& getPosition() const;
    const sf::Vector2f& getSize() const;
    bool isElementVisible() const;
    bool isElementActive() const;
}; 