#include "../../include/state/GameProcessState.hpp"

GameProcessState::GameProcessState(ResourceManager<sf::Texture>& textureManager)
    : textureManager(textureManager), player(createPlayer()) {
    infoLog("GameProcessState::GameProcessState", "Вызван конструктор");
}

Player GameProcessState::createPlayer() {
    infoLog("GameProcessState::createPlayer", "Вызван метод (игрок ещё не создан)");
    const auto& tilesetTexture = textureManager.get("tileset");

    // Параметры тайлсета
    const int tileSize = 12; // Размер тайла (12x12 пикселей)
    const int spacing = 1;   // Отступ между тайлами (1 пиксель)
    const int tilesPerRow = tilesetTexture.getSize().x / (tileSize + spacing); // Количество тайлов в строке

    // ID тайла, который нужно вырезать (начиная с 0)
    int tileID = 1648 - 1;

    // Вычисление позиции тайла в текстуре
    int tileX = (tileID % tilesPerRow) * (tileSize + spacing);
    int tileY = (tileID / tilesPerRow) * (tileSize + spacing);
    
    // Загрузка текстуры для персонажа
    sf::IntRect rect({tileX, tileY}, {tileSize, tileSize});
    const sf::Texture& playerTexture = textureManager.getSubTexture("tileset", "player", rect);
    sf::Sprite sprite(playerTexture);
    
    infoLog("GameProcessState::createPlayer", "Игрок создан");
    return Player(sf::Vector2f(48.f, 48.f), sprite, 100, 12.f);
}

void GameProcessState::handleInput(const std::optional<sf::Event>& event) {
    // Управление персонажем
    // if (event.is<sf::Event::KeyPressed>()) {
        float playerSpeed = player.getSpeed();
        const auto* keyEvent = event->getIf<sf::Event::KeyPressed>();
        
        switch (keyEvent->code) {
        case sf::Keyboard::Key::A:
            player.move({-playerSpeed, 0});
            break;
        case sf::Keyboard::Key::D:
            player.move({playerSpeed, 0});
            break;
        case sf::Keyboard::Key::W:
            player.move({0, -playerSpeed});
            break;
        case sf::Keyboard::Key::S:
            player.move({0, playerSpeed});
            break;
        default:
            break;
        }
    // }
}

void GameProcessState::render(sf::RenderWindow& window) {
    window.draw(player);
}