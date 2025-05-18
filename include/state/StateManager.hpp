#pragma once

#include <memory>
#include <stack>
#include "GameState.hpp"

class Game;
class GameState;


/**
 *  Класс для управления состояниями игры.
 *  Он отвечает за управление стеком состояний игры,
 *  добавление новых состояний, удаление верхнего состояния,
 *  изменение текущего состояния и отрисовку текущего состояния.
 */
class StateManager {
public:
    StateManager();

    // Существует ли текущее состояние
    bool isStateValid() const;

    // Добавляет новое состояние в стек
    void push(std::unique_ptr<GameState> state);

    // Удаляет верхнее состояние из стека
    void pop();

    // Меняет текущее состояние на новое
    void change(std::unique_ptr<GameState> state);

    // Отрисовывает текущее состояние
    void renderCurrent(sf::RenderWindow& window);

    // Обрабатывает события ввода
    void handleInput(const sf::Event& event);

private:
    // Стек состояний
    std::stack<std::unique_ptr<GameState>> states;
};