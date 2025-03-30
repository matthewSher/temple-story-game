#include "../../include/state/GameProcessState.hpp"

GameProcessState::GameProcessState(ResourceManager<sf::Texture, TextureKeys>& textureManager)
    : textureManager(textureManager) {
    infoLog("GameProcessState::GameProcessState", "Вызван конструктор");
    player = std::make_unique<Player>(textureManager);
}

void GameProcessState::handleInput(const sf::Event::KeyPressed *keyEvent) {
    switch (keyEvent->code) {
    case sf::Keyboard::Key::A:
        player->move({-1, 0});
        break;
    case sf::Keyboard::Key::D:
        player->move({1, 0});
        break;
    case sf::Keyboard::Key::W:
        player->move({0, -1});
        break;
    case sf::Keyboard::Key::S:
        player->move({0, 1});
        break;
    default:
        break;
    }
}

void GameProcessState::render(sf::RenderWindow& window) {
    window.draw(*player);
}