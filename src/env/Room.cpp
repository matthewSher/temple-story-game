#include "../../include/env/Room.hpp"

#include <filesystem>
#include <fstream>
#include <sstream>
#include "../../include/utils/logging.h"
#include "../../include/tools/ResourceManager_T.hpp"
#include "../../include/constants/main_constants.h"
#include "../../include/constants/path.h"
#include "../../include/utils/utils_functions.h"

namespace fs = std::filesystem;

Room::Room(ResourceManager<sf::Texture>& textureManager, const std::string& tilemapPath)
    : textureManager(textureManager) {
    infoLog("Room::Room", "Вызван конструктор");

    // Создание объекта TileMap
    roomTilemap = std::make_unique<TileMap>(textureManager.get("tileset"), 
                                            tmx::Vector2u(TILE_SIZE, TILE_SIZE));
    if (!roomTilemap->load(tilemapPath)) {
        errorLog("Room::Room", "Ошибка загрузки карты тайлов");
        throw std::runtime_error("Error loading tilemap");
    }

    loadStaticObjects();
}

void Room::placeStaticObjectsByConfigFile(const std::string& filepath) {
    std::ifstream  staticObjectsConfigFile(filepath);
    std::string line;

    if (!staticObjectsConfigFile.is_open()) {
        errorLog("Room::placeStaticObjects", "Не удалось открыть файл");
        return;
    }

    // Каждая считываемая строка имеет следующий формат:
    // <число> <число> <число>
    // Например:
    // 12 10 2000
    // 1 2 3
    // и т.д.
    // Первые два числа будут считываться как координаты расположения
    // статического объекта (в тайлах!!), а вторая - ID текстуры для объекта в
    // тайлсете
    while (std::getline(staticObjectsConfigFile, line)) {
        std::istringstream lineStream(line);
        int xCoordInTiles, yCoordInTiles; // Координаты позиции объекта (в тайлах)
        int textureId;

        // Последовательно читаем строку
        lineStream >> xCoordInTiles >> yCoordInTiles >> textureId;
        
        float xCoord = static_cast<float>(xCoordInTiles);
        float yCoord = static_cast<float>(yCoordInTiles);
        
        // Загрузка текстуры объекта
        std::string soName = "staticObject" + std::to_string(textureId);
        sf::IntRect rect(getTileCoordsById(textureId), {TILE_SIZE, TILE_SIZE});
        const sf::Texture& soTexture = textureManager.getSubTexture("tileset", soName, rect);

        // Создание объекта
        StaticObject so({(float) xCoord * TILE_SIZE, yCoord * TILE_SIZE}, sf::Sprite(soTexture));
        
        staticObjects.push_back(so);
    }   
}

void Room::loadStaticObjects() {
    std::string levelsFolder = LEVEL_PATH;

    try {
        // Перебор всех папок в levelsFolder
        for (const auto& levelFolder : fs::directory_iterator(levelsFolder)) {
            if (!levelFolder.is_directory()) continue;

            // Перебор всех папок в levelFolder
            for (const auto& roomFolder : fs::directory_iterator(levelFolder)) {
                if (!roomFolder.is_directory()) continue;

                // Перебор файлов в roomFolder
                for (const auto& file : fs::directory_iterator(roomFolder)) {
                    if (!file.is_regular_file()) continue;

                    std::string filepath = file.path().string();

                    if (file.path().filename().string() == STATIC_OBJECTS_CONFIG_FILENAME) {
                        infoLog("Room::loadStaticObjects", "Загружается файл: " + filepath);
                        placeStaticObjectsByConfigFile(filepath);
                    }
                }
            }
        }
    } catch(const fs::filesystem_error& e) {
        errorLog("Room::loadStaticObjects", "Ошибка при чтении файлов");
    }
}

bool Room::checkCollision(const sf::Vector2f& position) const {
    // Позиция передается в тайлах, поэтому умножаем на TILE_SIZE 
    // для получения позиции в пикселях, поскольку isTileCollidable ожидает позицию в пикселях
    sf::Vector2f playerPixelPos = {position.x * TILE_SIZE, position.y * TILE_SIZE};
    return roomTilemap->isTileCollidable(playerPixelPos);
}

void Room::render(sf::RenderWindow& window) {
    window.draw(*roomTilemap);
    for (const auto& so : staticObjects) {
        window.draw(so);
    }
}