#pragma once

#include <SFML/Graphics.hpp>

/**
 * Класс Camera отвечает за управление камерой в игре.
 * Он позволяет перемещать камеру в окне игры с помощью клавиш.
 */
class Camera {
private:
    // Вид камеры
    // sf::View - класс, который представляет собой вид на сцену
    // sf::View содержит в себе информацию о том, какую часть сцены мы видим
    // и как она масштабируется
    sf::View view;
    // Скорость перемещения камеры (в пикселях)
    float moveSpeed = 12.f;

public:
    Camera(sf::RenderWindow& window);

    // Обрабатывает ввод клавиш
    void handleInput(const sf::Event::KeyPressed* keyEvent);
    // Применяет вид камеры к окну
    void apply(sf::RenderWindow& window);
    // Устанавливает центр камеры
    void setCenter(const sf::Vector2f& center);
}; 