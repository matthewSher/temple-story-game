#pragma once

#include <memory>
#include <stack>
#include "GameState.hpp"

class Game;
class GameState;

class StateManager {
public:
    // Запрещаем создание без контекста
    StateManager(Game* gameContext) : context(gameContext) {
        infoLog("StateManager::StateManager", "Вызван конструктор");
        if(!context) {
            errorLog("StateManager::StateManager", "Контекст игры не может быть null");
            throw std::invalid_argument("Game context cannot be null");
        }
    }

    bool isStateValid() const {
        return !states.empty() && states.top() != nullptr;
    }

    void push(std::unique_ptr<GameState> state) {
        if(!state) return;
        
        // Приостанавливаем текущее состояние
        if(!states.empty()) {
            states.top()->onExit();
        }

        // Инициализируем и активируем новое состояние
        state->onEnter();
        states.push(std::move(state));
    }

    void pop() {
        if(states.empty()) return;
        
        states.top()->onExit();
        states.pop();

        if(!states.empty()) {
            states.top()->onEnter();
        }
    }

    void change(std::unique_ptr<GameState> state) {
        if (!state) return;    

        state->onEnter();    
    
        if (!states.empty()) {
            states.top()->onExit();
            states.pop();
        }

        states.push(std::move(state));
    }

    void renderCurrent(sf::RenderWindow& window) {
        if (!states.empty()) {
            states.top()->render(window);
        }
    }

    void handleInput(const sf::Event& event) {
        if (!states.empty()) {
            states.top()->handleInput(event);
        } else {
            errorLog("StateManager::handleInput", "Текущее состояние не найдено");
        }
    }

private:
    std::stack<std::unique_ptr<GameState>> states;
    Game* context;
};