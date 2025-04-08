#pragma once

#include <memory>
#include <SFML/Graphics.hpp>


/**
 * Класс GameState представляет собой абстрактный базовый класс для различных состояний игры.
 * Он определяет интерфейс для обработки ввода и отрисовки состояния игры.
 * Все конкретные состояния игры должны наследоваться от этого класса и реализовывать его методы.
 */
class GameState {
public:
    virtual ~GameState() = default;
     
    // Метод для обработки ввода от игрока
    // keyEvent - событие нажатия клавиши, которое нужно обработать
    virtual void handleInput(const sf::Event::KeyPressed *keyEvent) = 0;
    // Метод для отрисовки состояния игры на экране
    virtual void render(sf::RenderWindow& window) = 0;
};