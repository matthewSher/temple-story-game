#include "../../include/state/StateManager.hpp"
#include "../../include/utils/logging.h"

StateManager::StateManager(Game* gameContext) : context(gameContext) {
    infoLog("StateManager::StateManager", "Вызван конструктор");
    if(!context) {
        errorLog("StateManager::StateManager", "Контекст игры не может быть null");
        throw std::invalid_argument("Game context cannot be null");
    }
}

bool StateManager::isStateValid() const {
    return !states.empty() && states.top() != nullptr;
}

void StateManager::push(std::unique_ptr<GameState> state) {
    if(!state) return;
    
    // Приостанавливаем текущее состояние
    if(!states.empty()) {
        states.top()->onExit();
    }

    // Инициализируем и активируем новое состояние
    state->onEnter();
    states.push(std::move(state));
}

void StateManager::pop() {
    if(states.empty()) return;
    
    states.top()->onExit();
    states.pop();

    if(!states.empty()) {
        states.top()->onEnter();
    }
}

void StateManager::change(std::unique_ptr<GameState> state) {
    if (!state) return;    

    state->onEnter();    

    if (!states.empty()) {
        states.top()->onExit();
        states.pop();
    }

    states.push(std::move(state));
}

void StateManager::renderCurrent(sf::RenderWindow& window) {
    if (!states.empty()) {
        states.top()->render(window);
    }
}

void StateManager::handleInput(const sf::Event& event) {
    if (!states.empty()) {
        states.top()->handleInput(event);
    } else {
        errorLog("StateManager::handleInput", "Текущее состояние не найдено");
    }
}