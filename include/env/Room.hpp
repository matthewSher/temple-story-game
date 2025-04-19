#pragma once

#include <memory>
#include "../tools/TileMap.hpp"
#include "../tools/ResourceManager_T.hpp"
#include "../entities/StaticObject.hpp"

/**
 * Класс Room представляет собой игровую комнату, основу которой составляет тайловая карта
 * (roomTilemap).
 * Он отвечает за загрузку текстур, управление тайлами и проверку коллизий.
 * Он использует менеджер ресурсов для загрузки текстур и управления ими.
 */
class Room {
private:
    // Менеджер текстур для комнаты
    ResourceManager<sf::Texture>& textureManager;
    // Указатель на объект TileMap, который представляет собой тайловую карту комнаты
    std::unique_ptr<TileMap> roomTilemap;
    // Массив, хранящий все предметы, находящиеся в комнате
    std::vector<StaticObject> staticObjects;

    // Помещает в вектор staticObjects объекты по файлу-конфигурации,
    // расположенному по пути filepath
    void placeStaticObjectsByConfigFile(const std::string& filepath);

    // Метод для заполнения массива staticObjects
    void loadStaticObjects();
public:
    Room(ResourceManager<sf::Texture>& textureManager, const std::string& tilemapPath);

    // Метод для проверки коллизий между объектом и тайлом
    // position - позиция объекта, с которым проверяется коллизия (в пикселях)
    bool checkCollision(const sf::Vector2f& position) const;
    // Отрисовка комнаты на экране
    void render(sf::RenderWindow& window);
};