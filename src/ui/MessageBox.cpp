#include "../../include/ui/MessageBox.hpp"

#include "../../include/Game.hpp"

MessageBox::MessageBox() : UIElement(sf::Vector2f(0.f, 0.f), minSize) {
    shape.setFillColor(sf::Color(28, 28, 28));
    shape.setOutlineColor(sf::Color(220, 220, 220));
    shape.setOutlineThickness(2.f);
    
    centerOnScreen(Game::getInstance().getWindow()); // Принудительное центрирование
    setBounds(); // Обновляем границы
}

MessageBox::MessageBox(const sf::Vector2f& pos, const sf::Vector2f& size, const sf::Text text) 
    : UIElement(pos, size), text(text) {
    shape.setFillColor(sf::Color(28, 28, 28));
    shape.setOutlineColor(sf::Color(220, 220, 220));
    shape.setOutlineThickness(2.f);
    
    setBounds(); // Обновляем границы
}

void MessageBox::render(sf::RenderWindow& window) {
    if (!isElementVisible()) return;

    // Отрисовка окна
    window.draw(shape);

    // Отрисовка текста
    window.draw(text);
}

void MessageBox::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
    // Обрабатываем события только если окно видимо
    if (!isElementVisible()) return;

    if (auto keyEvent = event.getIf<sf::Event::KeyPressed>()) {
        if (keyEvent->code == sf::Keyboard::Key::Escape) {
            hide();
        }
    }
}

void MessageBox::setBounds() {
    // Получаем границы текста
    sf::FloatRect textBounds = text.getLocalBounds();
    
    // Рассчитываем размер окна с учётом отступов
    float width = std::max(textBounds.size.x + 16 * 2.f, minSize.x);
    float height = std::max(textBounds.size.y + 16 * 2.f, minSize.y);
    
    // Устанавливаем размер окна
    shape.setSize(sf::Vector2f(width, height));
}

void MessageBox::setText(const sf::String& string) {
    text.setString(sf::String::fromUtf8(string.begin(), string.end()));
    setBounds();
}

void MessageBox::centerOnScreen(const sf::RenderWindow& window) {
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2f boxSize = shape.getSize();
    
    // Рассчитываем позицию для центрирования
    float x = (windowSize.x - boxSize.x) / 2.f;
    float y = (windowSize.y - boxSize.y) / 2.f;
    
    // Устанавливаем новую позицию
    setPosition({x, y});

    setBounds();
}

// Методы для управления видимостью
void MessageBox::show() {
    setVisible(true);
}

void MessageBox::hide() {
    setVisible(false);
}