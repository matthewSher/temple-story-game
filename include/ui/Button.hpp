#pragma once

#include "UIElement.hpp"
#include <functional>

/**
 * Класс Button представляет собой кнопку в интерфейсе
 * Может содержать текст и выполнять действие при нажатии
 */
class Button : public UIElement {
private:
    sf::RectangleShape shape;                           // Форма кнопки
    sf::Text text;                                      // Текст на кнопке
    std::function<void()> onClickCallback;              // Функция, вызываемая при нажатии
    bool isHovered = false;                             // Флаг нахождения мыши над кнопкой
    sf::Color normalColor = sf::Color(100, 100, 100);   // Цвет кнопки в нормальном состоянии
    sf::Color hoverColor = sf::Color(150, 150, 150);    // Цвет кнопки при наведении

public:
    Button(const sf::Vector2f& pos, const sf::Vector2f& size, 
           const std::string& label, const sf::Font& font,
           std::function<void()> callback = nullptr);

    void render(sf::RenderWindow& window) override;
    void handleEvent(const sf::Event& event) override;

    void setText(const std::string& newText);
    void setCallback(std::function<void()> callback);
    void setColors(const sf::Color& normal, const sf::Color& hover);
}; 