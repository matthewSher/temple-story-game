#include "../../../include/entities/static_objects/Letter.hpp"

#include "../../../include/Game.hpp"
#include <iostream>

Letter::Letter(sf::Vector2f p, sf::Sprite s, const std::string& text) : StaticObject(p, s), text(text) {
    infoLog("Letter::Letter", "Создание объекта Letter");
    sf::Font font = Game::getInstance().getFontManager().get("regular");
    descriptionWindow = std::make_unique<MessageBox>(sf::Vector2f(0, 0), sf::Vector2f(350, 150), sf::Text(font, text));
}

void Letter::interact() {
    descriptionWindow->show();
}

