#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

class Game;

/**
 * Класс GameState представляет собой абстрактный базовый класс для различных состояний игры.
 * Он определяет интерфейс для обработки ввода и отрисовки состояния игры.
 * Все конкретные состояния игры должны наследоваться от этого класса и реализовывать его методы.
 */
class GameState {
public:
    GameState(Game* game) : context(game) {}
    virtual ~GameState() = default;
     
    // Метод для обработки ввода от игрока
    // keyEvent - событие нажатия клавиши, которое нужно обработать
    virtual void handleInput(const sf::Event& event) = 0;
    // Метод для отрисовки состояния игры на экране
    virtual void render(sf::RenderWindow& window) = 0;
    // Метод для активации состояния
    virtual void onEnter() = 0;
    // Метод для деактивации состояния
    virtual void onExit() = 0;
    
protected:
    Game* context; // Не может быть null
};