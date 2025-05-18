#pragma once

#include <map>
#include "GameState.hpp"
#include "../ui/UIElement.hpp"

class PlayerUIState : public GameState {
private:
    // Map указателей на объекты UIElement, представляющие UI элементы в интерфейсе игрока
    std::map<std::string, std::unique_ptr<UIElement>> uiElements;

    PlayerUIState(); 
public:
    PlayerUIState(const PlayerUIState&) = delete;
    PlayerUIState& operator=(const PlayerUIState&) = delete;

    // Метод для обработки ввода от игрока
    // keyEvent - событие нажатия клавиши, которое нужно обработать
    void handleInput(const sf::Event& event) override;

    // Метод для отрисовки состояния игры на экране
    void render(sf::RenderWindow& window) override;

    // Добавление UI элемента в map
    void addUIElement(const std::string& elementName, std::unique_ptr<UIElement> element);

    // Метод для активации состояния
    void onEnter() override;
    
    // Метод для деактивации состояния
    void onExit() override;

    // Метод для получения единственного объекта класса
    static PlayerUIState& getInstance();
};