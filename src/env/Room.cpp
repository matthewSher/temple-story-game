#include "../../include/env/Room.hpp"

#include "../../include/utils/logging.h"
#include "../../include/tools/ResourceManager_T.hpp"
#include "../../include/constants/TextureKeys.hpp"
#include "../../include/constants/main_constants.h"

Room::Room(ResourceManager<sf::Texture, TextureKeys>& textureManager, const std::string& tilemapPath) {
    infoLog("Room::Room", "Вызван конструктор");

    // Создание объекта TileMap
    roomTilemap = std::make_unique<TileMap>(textureManager.get(TextureKeys::Tileset), tmx::Vector2u(TILE_SIZE, TILE_SIZE));
    if (!roomTilemap->load(tilemapPath)) {
        errorLog("Room::Room", "Ошибка загрузки карты тайлов");
        throw std::runtime_error("Error loading tilemap");
    }
}

bool Room::checkCollision(const sf::Vector2f& position) const {
    sf::Vector2f playerPixelPos = {position.x * TILE_SIZE, position.y * TILE_SIZE};
    return roomTilemap->isTileCollidable(playerPixelPos);
}

void Room::render(sf::RenderWindow& window) {
    window.draw(*roomTilemap);
}