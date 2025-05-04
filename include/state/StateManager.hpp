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
        
        // Деактивируем текущее состояние
        states.top()->onExit();
        states.pop();

        // Возобновляем предыдущее состояние
        if(!states.empty()) {
            states.top()->onEnter();
        }
    }

    void change(std::unique_ptr<GameState> state) {
        if(!state) return;

        try {
            // Деактивируем все состояния
            while(!states.empty()) {
                states.top()->onExit();
                states.pop();
            }
            
            // Активируем новое состояние
            infoLog("StateManager::change", "Активируем новое состояние");
            state->onEnter();
            states.push(std::move(state));
        } catch (const std::exception& e) {
            errorLog("StateManager::change", "Ошибка при смене состояния: " + std::string(e.what()));
            throw; // Пробрасываем исключение дальше
        }
    }

    GameState* getCurrent() const {
        return states.empty() ? nullptr : states.top().get();
    }

private:
    std::stack<std::unique_ptr<GameState>> states;
    Game* context;
};