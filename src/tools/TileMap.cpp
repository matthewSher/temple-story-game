#include "../../include/tools/TileMap.hpp"
#include "../../include/utils/logging.h"

#include <iostream>

TileMap::TileMap(const sf::Texture& texture) : tilesetTexture(texture) {}

std::unique_ptr<sf::VertexArray> TileMap::createVertexArrayForLayer(const tmx::TileLayer& tileLayer, 
    const tmx::Vector2u& mapSize, const tmx::Vector2u& tileSize) {
    // Создание умного указателя на массив вершин
    auto vertexArray = std::make_unique<sf::VertexArray>();
    
    // Каждый тайл будет располагаться на паре треугольников, формирующих четырёхугольник
    vertexArray->setPrimitiveType(sf::PrimitiveType::Triangles);
    
    // Устанавливаем размер массива по формуле:
    // количество_тайлов * 6,
    // где 6 - общее кол-во вершин двух треугольников (по 3 на каждый)
    vertexArray->resize(mapSize.x * mapSize.y * 6);
    
    // Потайловый перебор текстуры тайлсета (где x, y - координаты тайла в тайлах, не в пикселях!)
    for (int y = 0; y < mapSize.y; y++) {
        for (int x = 0; x < mapSize.x; x++) {
            // x + y * mapSize.x - формула преобразования координат в обычный индекс
            const auto& tile = tileLayer.getTiles()[x + y * mapSize.x];

            if (tile.ID != 0) {
                // Заполнение тайла данными (позиция и текстура)
                fillVertexArrayWithTile(*vertexArray, x, y, tile, mapSize, tileSize);
            }
        }
    }

    return vertexArray;
}

void TileMap::fillVertexArrayWithTile(sf::VertexArray& vertexArray, int x, int y, 
    const tmx::TileLayer::Tile& tile, const tmx::Vector2u& mapSize, const tmx::Vector2u& tileSize) {
    
    int of = 1; // Толщина границы между тайлами в пикселях
    int tileID = tile.ID - 1;
    int tu = tileID % (tilesetTexture.getSize().x / (tileSize.x + of));
    int tv = tileID / (tilesetTexture.getSize().x / (tileSize.x + of));

    // Указатель на текущий тайл в VertexArray
    sf::Vertex* triangles = &(vertexArray)[(x + y * mapSize.x) * 6];

    // Задание позиции вершин для двух треугольников (для отображения в игре)
    // Треугольник (0, 1, 2)
    triangles[0].position = sf::Vector2f(x * tileSize.x, y * tileSize.y);
    triangles[1].position = sf::Vector2f((x + 1) * tileSize.x, y * tileSize.y);
    triangles[2].position = sf::Vector2f((x + 1) * tileSize.x, (y + 1) * tileSize.y);

    // Треугольник (2, 3, 0)
    triangles[3].position = sf::Vector2f(triangles[2].position);
    triangles[4].position = sf::Vector2f(x * tileSize.x, (y + 1) * tileSize.y);
    triangles[5].position = sf::Vector2f(triangles[0].position);

    // "Вырезаем" нужный тайл из текстуры тайлсета
    // Треугольник (0, 1, 2)
    triangles[0].texCoords = sf::Vector2f(tu * (tileSize.x + of) + of, tv * (tileSize.y + of) + of);
    triangles[1].texCoords = sf::Vector2f((tu + 1) * (tileSize.x + of), tv * (tileSize.y + of) + of);
    triangles[2].texCoords = sf::Vector2f((tu + 1) * (tileSize.x + of), (tv + 1) * (tileSize.y + of));
    
    // Треугольник (2, 3, 0)
    triangles[3].texCoords = sf::Vector2f(triangles[2].texCoords);
    triangles[4].texCoords = sf::Vector2f(tu * (tileSize.x + of) + of, (tv + 1) * (tileSize.y + of));
    triangles[5].texCoords = sf::Vector2f(triangles[0].texCoords);
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.texture = &tilesetTexture;

    for (const auto& layer : layersVertexArray) {
        target.draw(*layer, states);
    }
}

bool TileMap::load(const std::string& tmxFile) {
    tmx::Map map;
    if (!map.load(tmxFile)) {
        errorLog("TileMap::load", "Не удалось загрузить tilemap");
        return false;
    }

    const auto& tileSize = map.getTileSize();
    const auto& mapSize = map.getTileCount();

    for (const auto& layer : map.getLayers()) {
        // Пропускаем слои, которые не являются тайловыми (например, объектные слои)
        if (layer->getType() != tmx::Layer::Type::Tile) continue;

        // Приведение слоя к типу TileLayer
        const auto& tileLayer = layer->getLayerAs<tmx::TileLayer>();

        auto vertexArray = createVertexArrayForLayer(tileLayer, mapSize, tileSize);
        layersVertexArray.push_back(std::move(vertexArray));
    }

    return true;
}
