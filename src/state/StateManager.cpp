#include "../../include/state/StateManager.hpp"
#include "../../include/utils/logging.h"

StateManager::StateManager() {
    infoLog("StateManager::StateManager", "Вызван конструктор");
}

bool StateManager::isStateValid() const {
    return !states.empty() && states.top() != nullptr;
}

void StateManager::push(std::unique_ptr<GameState> state) {
    if(!state) return;
    
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
