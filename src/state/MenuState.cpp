#include "../../include/state/MenuState.hpp"

#include "../../include/constants/game_settings.hpp"
#include "../../include/Game.hpp"
#include "../../include/ui/Button.hpp"
#include <functional>

MenuState::MenuState() {
    infoLog("MenuState::MenuState", "Вызван конструктор");
}

void MenuState::handleInput(const sf::Event& event) {
    if (uiElements.empty()) return;
    // Обработка событий мыши для всех UI элементов

    for (auto& element : uiElements) {
        if (element && element->isElementActive()) {
            element->handleEvent(event, Game::getInstance().getWindow());
        }
    }
}

void MenuState::render(sf::RenderWindow& window) {
    // Отрисовка всех UI элементов
    for (auto& element : uiElements) {
        if (element->isElementVisible()) {
            element->render(window);
        }
    }
}

void MenuState::onEnter() {
    infoLog("MenuState::onEnter", "Вызван метод onEnter");

    Game& gameInstance = Game::getInstance();

    auto& fontManager = gameInstance.getFontManager();

    // Кнопка "Начать игру"
    auto startButton = std::make_unique<Button>(
        sf::Vector2f(590, 320),     // Позиция
        sf::Vector2f(100, 25),      // Размер
        "Начать игру",              // Текст
        fontManager.get("regular"), // Шрифт
        [&]() {                  // Callback
            auto newState = std::make_unique<GameProcessState>();
            gameInstance.changeState(std::move(newState));
        }
    );
    startButton->setCameraView(&gameInstance.getWindow().getView());
    addUIElement(std::move(startButton));

    // Кнопка "Выйти из игры"
    auto exitButton = std::make_unique<Button>(
        sf::Vector2f(585, 380),     // Позиция
        sf::Vector2f(110, 25),      // Размер
        "Выйти из игры",            // Текст
        fontManager.get("regular"), // Шрифт
        [&]() {                     // Callback
            gameInstance.closeWindow();
        }
    );
    exitButton->setCameraView(&gameInstance.getWindow().getView());
    addUIElement(std::move(exitButton));
}

void MenuState::onExit() {
    infoLog("MenuState::onExit", "Вызван метод onExit");
}

void MenuState::addUIElement(std::unique_ptr<UIElement> element) {
    uiElements.push_back(std::move(element));
}