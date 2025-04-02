#include "../../include/env/Room.hpp"

#include "../../include/utils/logging.h"
#include "../../include/tools/ResourceManager_T.hpp"
#include "../../include/constants/TextureKeys.hpp"

Room::Room(ResourceManager<sf::Texture, TextureKeys>& textureManager, const std::string& tilemapPath) {
    infoLog("Room::Room", "Вызван конструктор");

    // Создание объекта TileMap
    roomTilemap = std::make_unique<TileMap>(textureManager.get(TextureKeys::Tileset));
    if (!roomTilemap->load(tilemapPath)) {
        errorLog("Room::Room", "Ошибка загрузки карты тайлов");
        throw std::runtime_error("Error loading tilemap");
    }
}

void Room::render(sf::RenderWindow& window) {
    window.draw(*roomTilemap);
}