#include "../../include/entities/Player.hpp"

Player::Player(ResourceManager<sf::Texture>& textureManager) 
    : Character(sf::Vector2f(48.f, 48.f), createSprite(textureManager), 100, 12.f) {}

sf::Sprite Player::createSprite(ResourceManager<sf::Texture>& textureManager) {
    infoLog("Player::createSprite", "Вызван метод");
    const auto& tilesetTexture = textureManager.get("tileset");

    // Параметры тайлсета
    const int tileSize = 12; // Размер тайла (12x12 пикселей)
    const int of = 1;        // Отступ между тайлами (1 пиксель)
    const int tilesPerRow = tilesetTexture.getSize().x / (tileSize + of); // Количество тайлов в строке

    // ID тайла, который нужно вырезать (начиная с 0)
    int tileID = 1648;

    // Вычисление позиции тайла (в тайлах)
    int tu = tileID % tilesPerRow;
    int tv = tileID / tilesPerRow;
    
    // Вычисление позиции тайла (в пикселях)
    int tileX = tu * (tileSize + of) + of;
    int tileY = tv * (tileSize + of) + of;

    // Загрузка текстуры для персонажа
    sf::IntRect rect({tileX, tileY}, {tileSize, tileSize});
    const sf::Texture& playerTexture = textureManager.getSubTexture("tileset", "player", rect);
    
    return sf::Sprite(playerTexture);
}