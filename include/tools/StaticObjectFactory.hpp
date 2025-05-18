#pragma once

#include <unordered_map>
#include <string>
#include <functional>
#include <memory>
#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include "../entities/StaticObject.hpp"

using json = nlohmann::json;

/**
 * Класс StaticObjectFactory отвечает за создание статических объектов в игре.
 * Он использует паттерн проектирования "Фабрика" для создания объектов.
 * 
 * В классе используется std::unordered_map для хранения функций создания объектов,
 * которые могут быть вызваны по имени объекта.
 */
class StaticObjectFactory {
    // Тип для функции создания статического объекта
    using Creator = std::function<std::unique_ptr<StaticObject>(const sf::Vector2f, const sf::Sprite, const json& objectData)>;
private:
    // Хранит функции создания статических объектов
    std::unordered_map<std::string, Creator> creators;

    StaticObjectFactory();

public:
    StaticObjectFactory(const StaticObjectFactory&) = delete;
    StaticObjectFactory& operator=(const StaticObjectFactory&) = delete;
    
    // Метод для обращения к единственному экземпляру класса
    static StaticObjectFactory& getInstance();

    // Метод для регистрации нового типа статического объекта
    void registerObject(const std::string& objectName, Creator creator);

    // Метод для создания статического объекта по имени
    // Принимает имя объекта, позицию и спрайт
    std::unique_ptr<StaticObject> createObject(
        const json& objectData, sf::Vector2f position, sf::Sprite sprite
    );
};