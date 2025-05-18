#include "UIElement.hpp"

#include "../Game.hpp"

class MessageBox : public UIElement {
private:
    sf::RectangleShape shape;                                   // Форма текстового окна
    sf::Text text = {                                           // Текстовое содержание
        Game::getInstance().getFontManager().get("regular"), 
        "Message Box"
    };                                      
    sf::Vector2f minSize = {350.f, 150.f};                      // Минимальный размер окна

public:
    MessageBox();
    MessageBox(const sf::Vector2f& pos, const sf::Vector2f& size, const sf::Text text);

    // Отрисовка элемента
    void render(sf::RenderWindow& window) override;
    
    // Обработка событий
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window) override;

    // Установка размера и позиции окна
    void setBounds();

    // Установка текста
    void setText(const sf::String& string);
    
    // Центрирование окна на экране
    void centerOnScreen(const sf::RenderWindow& window);

    // Методы для управления видимостью
    void show();
    void hide();
};