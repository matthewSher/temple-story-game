#include "../../include/ui/UIElement.hpp"
#include "../../include/constants/game_settings.hpp"

UIElement::UIElement(const sf::Vector2f& pos, const sf::Vector2f& size)
    : position(pos), size(size) {}

bool UIElement::contains(const sf::Vector2f& point, const sf::RenderWindow& window) const {
    if (!cameraView) {
        return point.x >= position.x && point.x <= position.x + size.x &&
               point.y >= position.y && point.y <= position.y + size.y;
    }

    // Преобразуем координаты мыши из координат окна в координаты вида камеры
    sf::Vector2f worldPoint = window.mapPixelToCoords(
        sf::Vector2i(point.x, point.y),
        *cameraView
    );

    return worldPoint.x >= position.x && worldPoint.x <= position.x + size.x &&
           worldPoint.y >= position.y && worldPoint.y <= position.y + size.y;
}

void UIElement::setCameraView(const sf::View* view) {
    cameraView = view;
}

void UIElement::setPosition(const sf::Vector2f& pos) {
    position = pos;
}

void UIElement::setSize(const sf::Vector2f& newSize) {
    size = newSize;
}

void UIElement::setVisible(bool visible) {
    isVisible = visible;
}

void UIElement::setActive(bool active) {
    isActive = active;
}

const sf::Vector2f& UIElement::getPosition() const {
    return position;
}

const sf::Vector2f& UIElement::getSize() const {
    return size;
}

bool UIElement::isElementVisible() const {
    return isVisible;
}

bool UIElement::isElementActive() const {
    return isActive;
}