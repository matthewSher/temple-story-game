#include "../../include/state/MenuState.hpp"
#include "../../include/constants/game_settings.hpp"
#include "../../include/Game.hpp"
#include "../../include/ui/Button.hpp"
#include <functional>

MenuState::MenuState(Game* gameContext) : GameState(gameContext) {
    infoLog("MenuState::MenuState", "Вызван конструктор");
}

void MenuState::handleInput(const sf::Event& event) {
    if (!context || !context->getWindow().isOpen()) return;
    
    // Обработка событий мыши для всех UI элементов
    if (!uiElements.empty()) {
        for (auto& element : uiElements) {
            if (element && element->isElementActive()) {
                element->handleEvent(event, context->getWindow());
            }
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

    auto& fontManager = context->getFontManager();

    // Кнопка "Начать игру"
    auto startButton = std::make_unique<Button>(
        sf::Vector2f(590, 320),     // Позиция
        sf::Vector2f(100, 25),      // Размер
        "Начать игру",              // Текст
        fontManager.get("regular"), // Шрифт
        [this]() {                  // Callback
            try {
                if (context && context->getWindow().isOpen()) {
                    auto newState = std::make_unique<GameProcessState>(context);
                    if (newState) {
                        // Отключение всех UI элементов перед сменой состояния
                        for (auto& element : uiElements) {
                            if (element) {
                                element->setActive(false);
                            }
                        }
                        context->changeState(std::move(newState));
                    } else {
                        errorLog("MenuState::onEnter", "Не удалось создать новое состояние");
                    }
                }
            } catch (const std::exception& e) {
                errorLog("MenuState::onEnter", "Ошибка при создании нового состояния: " + std::string(e.what()));
            }
        }
    );
    startButton->setCameraView(&context->getWindow().getView());
    addUIElement(std::move(startButton));

    // Кнопка "Выйти из игры"
    auto exitButton = std::make_unique<Button>(
        sf::Vector2f(585, 380),     // Позиция
        sf::Vector2f(110, 25),      // Размер
        "Выйти из игры",            // Текст
        fontManager.get("regular"), // Шрифт
        [this]() {                  // Callback
            if (context) {
                context->closeWindow();
            }
        }
    );
    exitButton->setCameraView(&context->getWindow().getView());
    addUIElement(std::move(exitButton));
}

void MenuState::onExit() {
    infoLog("MenuState::onExit", "Вызван метод onExit");
}

void MenuState::addUIElement(std::unique_ptr<UIElement> element) {
    uiElements.push_back(std::move(element));
}