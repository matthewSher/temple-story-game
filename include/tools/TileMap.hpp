#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>

/**
 * Класс TileMap предназначен для отрисовки карты тайлов. Он наследуется
 * от класса SFML sf::Drawable, чтобы иметь возможность отрисоваться на
 * экране.
 * 
 * Чтобы отрисовать карту, необходимо иметь саму карту тайлов формата .tmx,
 * а также тайлсет (два файла: .tsx файл, представляющий собой сам тайлсет, и
 * текстуру с набором тайлов для тайлсета).
 */

class TileMap : public sf::Drawable {
private:
    const sf::Texture& tilesetTexture;                               // Хранит текстуру для тайлсета
    std::vector<std::unique_ptr<sf::VertexArray>> layersVertexArray; // Массив слоёв карты тайлов
    
    // Возвращает массив вершин для слоя tileLayer тайл карты. Во избежание
    // копирования массива вершин, он обёрнут в умный указатель
    std::unique_ptr<sf::VertexArray> createVertexArrayForLayer(
        const tmx::TileLayer& tileLayer, const tmx::Vector2u& mapSize, const tmx::Vector2u& tileSize);
    
    // Заполняет vertexArray данными для конкретного тайла.
    // x и y - позиции тайла в тайлсете (измеряются в тайлах, не в пикселях!)
    void fillVertexArrayWithTile(sf::VertexArray& vertexArray, int x, int y,
        const tmx::TileLayer::Tile& tile, const tmx::Vector2u& mapSize, const tmx::Vector2u& tileSize);

protected:
    // Переопределение (override) чисто виртуального метода draw базового класса sf::Drawable.
    // Предназначен для отрисовки карты тайлов
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    // Конструктор, принимающий текстуру тайлсета
    TileMap(const sf::Texture& texture);

    // Подготовка карты тайлов перед рендером на экране
    bool load(const std::string& tmxFile);
};