#include "GameState.hpp"
#include "../ui/UIElement.hpp"



class PlayerUIState : public GameState {
private:

    std::unique_ptr<UIElement> messageBox;


    // keyEvent - событие нажатия клавиши, которое нужно обработать
    virtual void handleInput(const sf::Event& event) = 0;
    // Метод для отрисовки состояния игры на экране
    virtual void render(sf::RenderWindow& window) = 0;
    // Метод для активации состояния
    virtual void onEnter() = 0;
    // Метод для деактивации состояния
    virtual void onExit() = 0;

};