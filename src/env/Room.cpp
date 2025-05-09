#include "../../include/env/Room.hpp"

#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
#include "../../include/utils/logging.h"
#include "../../include/tools/ResourceManager_T.hpp"
#include "../../include/constants/main_constants.h"
#include "../../include/constants/path.h"
#include "../../include/utils/utils_functions.h"
#include "../../include/tools/StaticObjectFactory.hpp"

using json = nlohmann::json;
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
    // Данные об объектах хранятся в json файле
    std::ifstream  staticObjectsConfigFile(filepath);
    // Читаем данные из json файла
    json staticObjectsData = json::parse(staticObjectsConfigFile);

    if (!staticObjectsConfigFile.is_open()) {
        errorLog("Room::placeStaticObjectsByConfigFile", "Не удалось открыть файл");
        return;
    }

    // Перебор всех объектов в json файле
    for (const auto& object : staticObjectsData) {
        // Перевод координат из тайлов в пиксели
        float xCoord = static_cast<float>(object["tile_coords"][0]) * TILE_SIZE;
        float yCoord = static_cast<float>(object["tile_coords"][1]) * TILE_SIZE;
        int textureId = object["tile_id"];              // ID текстуры объекта
        std::string objectName = object["object_name"]; // Имя объекта

        // Загрузка текстуры объекта
        // rect - прямоугольник с координатами (x, y) и размерами (TILE_SIZE, TILE_SIZE),
        // по нему текстура объекта будет вырезана из тайлсета
        sf::IntRect rect(getTileCoordsById(textureId), {TILE_SIZE, TILE_SIZE});
        // "Вырезание" текстуры объекта из тайлсета
        const sf::Texture& soTexture = textureManager.getSubTexture("tileset", objectName, rect);

        // Экземпляр объекта создается при помощи соответствующей фабрики
        // и передается в вектор staticObjects
        StaticObjectFactory& factory = StaticObjectFactory::getInstance();
        auto so = factory.createObject(objectName, {xCoord, yCoord}, sf::Sprite(soTexture));

        if (!so) {
            errorLog("Room::placeStaticObjectsByConfigFile", "Не удалось создать объект: " + objectName);
            continue;
        }

        // Добавление объекта в вектор staticObjects
        staticObjects.push_back(std::move(so));
        infoLog("Room::placeStaticObjectsByConfigFile", "Создан объект: " + objectName + 
                " с ID текстуры: " + std::to_string(textureId) +
                " по координатам: (" + std::to_string(static_cast<int>(xCoord)) + 
                ", " + std::to_string(static_cast<int>(yCoord)) + ")"
        );
    }

    // while (std::getline(staticObjectsConfigFile, line)) {
    //     std::istringstream lineStream(line);
    //     int xCoordInTiles, yCoordInTiles; // Координаты позиции объекта (в тайлах)
    //     int textureId;
    //     std::string objectName;

    //     // Последовательно читаем строку
    //     lineStream >> xCoordInTiles >> yCoordInTiles >> textureId >> objectName;
    //     if (lineStream.fail()) {
    //         errorLog("Room::placeStaticObjectsByConfigFile", "Ошибка при считывании строки: " + line);
    //         continue;
    //     }
        
    //     float xCoord = static_cast<float>(xCoordInTiles * TILE_SIZE);
    //     float yCoord = static_cast<float>(yCoordInTiles * TILE_SIZE);
        
    //     // Загрузка текстуры объекта
    //     sf::IntRect rect(getTileCoordsById(textureId), {TILE_SIZE, TILE_SIZE});
    //     const sf::Texture& soTexture = textureManager.getSubTexture("tileset", objectName, rect);

    //     // Создание объекта статического объекта
    //     // Используем фабрику для создания статических объектов
    //     StaticObjectFactory& factory = StaticObjectFactory::getInstance();
    //     auto so = factory.createObject(objectName, {xCoord, yCoord}, sf::Sprite(soTexture));
    //     if (!so) {
    //         errorLog("Room::placeStaticObjectsByConfigFile", "Не удалось создать объект: " + objectName);
    //         continue;
    //     }
    //     staticObjects.push_back(std::move(so));
    //     infoLog("Room::placeStaticObjectsByConfigFile", "Создан объект: " + objectName + 
    //             " с ID текстуры: " + std::to_string(textureId) +
    //             " по координатам: (" + std::to_string(static_cast<int>(xCoord)) + 
    //             ", " + std::to_string(static_cast<int>(yCoord)) + ")"
    //     );
    // }   
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

void Room::interactWithStaticObjectAt(const sf::Vector2f& playerPosition) {
    const sf::Vector2f pixPlayerPos = {playerPosition.x * TILE_SIZE, playerPosition.y * TILE_SIZE};
    for (const auto& so : staticObjects) {
        if (so->getPosition() == pixPlayerPos) 
            so->interact();
    }
}

bool Room::checkCollision(const sf::Vector2f& position) const {
    // Позиция передается в тайлах, поэтому умножаем на TILE_SIZE 
    // для получения позиции в пикселях, поскольку isTileCollidable ожидает позицию в пикселях
    sf::Vector2f playerPixelPos = {position.x * TILE_SIZE, position.y * TILE_SIZE};
    return roomTilemap->isTileCollidable(playerPixelPos);
}

void Room::render(sf::RenderWindow& window) {
    try {
        if (!roomTilemap) {
            errorLog("Room::render", "TileMap не инициализирован");
            return;
        }

        window.draw(*roomTilemap);

        for (const auto& so : staticObjects) {
            if (so) {
                window.draw(*so);
            }
        }
    } catch (const std::exception& e) {
        errorLog("Room::render", "Ошибка при отрисовке: " + std::string(e.what()));
        throw;
    }
}