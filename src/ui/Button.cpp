#include "../../include/ui/Button.hpp"

Button::Button(const sf::Vector2f& pos, const sf::Vector2f& size, 
               const std::string& label, const sf::Font& font,
               std::function<void()> callback)
    : UIElement(pos, size), onClickCallback(callback), text(font,label) {
    
    // Настройка формы кнопки
    shape.setPosition(position);
    shape.setSize(size);
    shape.setFillColor(normalColor);
    shape.setOutlineThickness(2.f);
    shape.setOutlineColor(sf::Color::White);

    // Настройка текста
    text.setFont(font);
    text.setString(label);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);

    // Центрирование текста
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition(
        {position.x + (size.x - textBounds.size.x) / 2.f,
        position.y + (size.y - textBounds.size.y) / 2.f}
    );
}

void Button::render(sf::RenderWindow& window) {
    if (!isVisible) return;

    // Отрисовка фона кнопки
    shape.setFillColor(isHovered ? hoverColor : normalColor);
    window.draw(shape);

    // Отрисовка текста
    window.draw(text);
}

void Button::handleEvent(const sf::Event& event) {
    if (!isActive) return;

    if (event.is<sf::Event::MouseMoved>()) {
        sf::Vector2f mousePos(
            event.getIf<sf::Event::MouseMoved>()->position.x, 
            event.getIf<sf::Event::MouseMoved>()->position.y
        );
        // Проверка нахождения мыши над кнопкой
        isHovered = contains(mousePos);
    }
    else if (event.is<sf::Event::MouseButtonPressed>()) {
        if (event.getIf<sf::Event::MouseButtonPressed>()->button == sf::Mouse::Button::Left) {
            sf::Vector2f mousePos(
                event.getIf<sf::Event::MouseButtonPressed>()->position.x, 
                event.getIf<sf::Event::MouseButtonPressed>()->position.y
            );
            // Проверка нахождения мыши над кнопкой и вызов callback
            if (contains(mousePos) && onClickCallback) {
                onClickCallback();
            }
        }
    }
}

void Button::setText(const std::string& newText) {
    text.setString(newText);
    
    // Перецентрирование текста
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition({
        position.x + (size.x - textBounds.size.x) / 2.f,
        position.y + (size.y - textBounds.size.y) / 2.f
    });
}

void Button::setCallback(std::function<void()> callback) {
    onClickCallback = callback;
}

void Button::setColors(const sf::Color& normal, const sf::Color& hover) {
    normalColor = normal;
    hoverColor = hover;
} 