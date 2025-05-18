#pragma once

#include "GameState.hpp"
#include "../ui/UIElement.hpp"
#include "../ui/Button.hpp"
#include "../tools/ResourceManager_T.hpp"
#include <vector>
#include <memory>

/**
 * Класс MenuState представляет собой состояние меню игры
 * Управляет всеми UI элементами и их взаимодействием
 */
class MenuState : public GameState {
private:
    // Вектор указателей на объекты UIElement, представляющие UI элементы в меню
    std::vector<std::unique_ptr<UIElement>> uiElements;

public:
    MenuState();
    
    // Обработка событий
    void handleInput(const sf::Event& event) override;

    // Добавление UI элемента в вектор
    void addUIElement(std::unique_ptr<UIElement> element);

    // Метод для активации состояния
    void onEnter() override;

    // Метод для деактивации состояния
    void onExit() override;
    
    // Отрисовка UI элементов
    void render(sf::RenderWindow& window) override;
}; 