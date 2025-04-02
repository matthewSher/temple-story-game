#pragma once

#include <memory>
#include "../tools/TileMap.hpp"
#include "../tools/ResourceManager_T.hpp"

enum class TextureKeys;

class Room {
private:
    std::unique_ptr<TileMap> roomTilemap;
public:
    Room(ResourceManager<sf::Texture, TextureKeys>& textureManager, const std::string& tilemapPath);

    void render(sf::RenderWindow& window);
};