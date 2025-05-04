#include "../../include/tools/Camera.hpp"
#include "../../include/constants/game_settings.hpp"

Camera::Camera(sf::RenderWindow& window) {
    view = window.getView();
    view.setSize(sf::Vector2f(window.getSize()) / GameSettings::CAMERA_ZOOM_FACTOR);
    window.setView(view);
}

void Camera::handleInput(const sf::Event::KeyPressed* keyEvent) {
    if (!keyEvent) return;

    switch (keyEvent->code) {
        case sf::Keyboard::Key::Left:
            view.move({-GameSettings::CAMERA_MOVE_SPEED, 0});
            break;
        case sf::Keyboard::Key::Right:
            view.move({GameSettings::CAMERA_MOVE_SPEED, 0});
            break;
        case sf::Keyboard::Key::Up:
            view.move({0, -GameSettings::CAMERA_MOVE_SPEED});
            break;
        case sf::Keyboard::Key::Down:
            view.move({0, GameSettings::CAMERA_MOVE_SPEED});
            break;
    }
}

void Camera::apply(sf::RenderWindow& window) {
    window.setView(view);
}

void Camera::setCenter(const sf::Vector2f& center) {
    view.setCenter(center);
} 