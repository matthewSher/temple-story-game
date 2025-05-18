#include "../../include/state/PlayerUIState.hpp"

#include "../../include/Game.hpp"
#include "../../include/ui/UIElement.hpp"
#include "../../include/ui/MessageBox.hpp"

PlayerUIState::PlayerUIState() {
    infoLog("PlayerUIState::PlayerUIState", "Вызван конструктор");
}

void PlayerUIState::handleInput(const sf::Event& event) {
    if (uiElements.empty()) return;
    // Обработка событий мыши для всех UI элементов

    for (auto& element : uiElements) {
        if (element.second && element.second->isElementActive()) {
            element.second->handleEvent(event, Game::getInstance().getWindow());
        }
    }
}

void PlayerUIState::render(sf::RenderWindow& window) {
    // Отрисовка всех UI элементов
    for (auto& element : uiElements) {
        if (element.second && element.second->isElementVisible()) {
            element.second->render(window);
        }
    }
}

void PlayerUIState::addUIElement(const std::string& elementName, std::unique_ptr<UIElement> element) {
    uiElements[elementName] = std::move(element);
}

void PlayerUIState::onEnter() {
    infoLog("PlayerUIState::onEnter", "Вызван метод");

    // Создание объекта текстового окна для отображения
    // всех текстовых сообщений в игре
    auto messageBox = std::make_unique<MessageBox>();
    addUIElement("messageBox", std::move(messageBox));

}

void PlayerUIState::onExit() {
    infoLog("PlayerUIState::onExit", "Вызван метод");
}

PlayerUIState& PlayerUIState::getInstance() {
    static PlayerUIState instance; // Создаём единственный экземпляр класса
    return instance;
}