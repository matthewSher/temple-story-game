#include "../../include/state/PlayerUIState.hpp"

#include "../../include/Game.hpp"
#include "../../include/ui/UIElement.hpp"
#include "../../include/ui/MessageBox.hpp"

PlayerUIState::PlayerUIState() {}

void PlayerUIState::handleInput(const sf::Event& event) {
    if (uiElements.empty()) return;
    // Обработка событий мыши для всех UI элементов

    for (auto& element : uiElements) {
        if (element && element->isElementActive()) {
            element->handleEvent(event, Game::getInstance().getWindow());
        }
    }
}

void PlayerUIState::render(sf::RenderWindow& window) {
    // Отрисовка всех UI элементов
    for (auto& element : uiElements) {
        if (element->isElementVisible()) {
            element->render(window);
        }
    }
}

void PlayerUIState::addUIElement(std::unique_ptr<UIElement> element) {
    uiElements.push_back(std::move(element));
}

void PlayerUIState::onEnter() {
    infoLog("PlayerUIState::onEnter", "Вызван метод");

    // Создание объекта текстового окна для отображения
    // всех текстовых сообщений в игре
    auto messageBox = std::make_unique<MessageBox>();

}

void PlayerUIState::onExit() {
    infoLog("PlayerUIState::onExit", "Вызван метод");
}
