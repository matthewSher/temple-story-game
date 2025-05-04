#include "../../include/entities/Player.hpp"

#include "../../include/constants/main_constants.h"
#include "../../include/utils/utils_functions.h"

Player::Player(ResourceManager<sf::Texture>& textureManager) 
    : Character(sf::Vector2f(48.f, 48.f), createSprite(textureManager), 100, 12.f) {}

sf::Sprite Player::createSprite(ResourceManager<sf::Texture>& textureManager) {
    infoLog("Player::createSprite", "Вызван метод");

    // ID тайла, который нужно вырезать (начиная с 0)
    int tileID = 1648;

    // Проверяем, что ID тайла не превышает максимальное количество тайлов
    if (tileID >= TILE_COUNT_IN_ONE_ROW * TILE_COUNT_IN_ONE_ROW) {
        errorLog("Player::createSprite", "ID тайла вне диапазона: " + std::to_string(tileID));
        throw std::runtime_error("Tile ID out of range");
    }

    sf::Vector2i tileCoords = getTileCoordsById(tileID);
    infoLog("Player::createSprite", "Координаты тайла: (" + std::to_string(tileCoords.x) + ", " + std::to_string(tileCoords.y) + ")");
    
    // Загрузка текстуры для персонажа
    sf::IntRect rect(tileCoords, {TILE_SIZE, TILE_SIZE});
    const sf::Texture& playerTexture = textureManager.getSubTexture("tileset", "player", rect);
    
    return sf::Sprite(playerTexture);
}