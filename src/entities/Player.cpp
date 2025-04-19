#include "../../include/entities/Player.hpp"

#include "../../include/constants/main_constants.h"
#include "../../include/utils/utils_functions.h"

Player::Player(ResourceManager<sf::Texture>& textureManager) 
    : Character(sf::Vector2f(48.f, 48.f), createSprite(textureManager), 100, 12.f) {}

sf::Sprite Player::createSprite(ResourceManager<sf::Texture>& textureManager) {
    infoLog("Player::createSprite", "Вызван метод");

    // ID тайла, который нужно вырезать (начиная с 0)
    int tileID = 1648;

    sf::Vector2i tileCoords = getTileCoordsById(tileID);
    // Загрузка текстуры для персонажа
    sf::IntRect rect(tileCoords, {TILE_SIZE, TILE_SIZE});
    const sf::Texture& playerTexture = textureManager.getSubTexture("tileset", "player", rect);
    
    return sf::Sprite(playerTexture);
}