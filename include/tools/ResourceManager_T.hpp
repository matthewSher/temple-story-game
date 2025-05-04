#pragma once

#include <map>
#include <string>
#include <stdexcept>
#include "../utils/logging.h"

/**
 * Этот класс является шаблонным, поэтому его реализация находится в заголовочном файле.
 * Класс предназначен для загрузки ресурсов из файловой системы.
 * 
 * Обёрнут шаблоном Resource, который может быть одним из трёх SFML классов:
 * sf::Texture, sf::Font, sf::SoundBuffer.
 */
template <typename Resource>
class ResourceManager {
private:
    // В этот словарь помещаются все загруженные ресурсы
    std::map<std::string, Resource> resources;

public:
    // Метод, по которому можно получить соответствующий ресурс.
    // В качестве параметра передаётся название ресурса (name)
    Resource& get(const std::string& name) {
        auto it = resources.find(name); // Ищет ресурс по имени внутри map
    
        // Если ресурс не найден
        if (it == resources.end()) {
            errorLog("ResourceManager::get", "Ресурс " + name + " не найден");
            throw std::runtime_error("Resources not found");
        }
    
        // Если ресурс найден, it указывает на пару ключ-значение std::pair<std::string, Resource>.
        // Возвращаем сам ресурс, т.е. второе значение

        infoLog("ResourceManager::get", "Ресурс " + name + " успешно получен");
        return it->second;
    }

    // Метод для загрузки ресурсов. Принимает в качестве аргументов
    // название ресурса (name) и путь к нему (path)
    template <typename T = Resource>
    bool load(std::string name, const std::string& path) {
        if (resources.find(name) != resources.end()) {
            errorLog("ResourceManager::load", "Ресурс уже загружен");
            return false;
        }

        Resource resource;
        bool loadResult = false;
        
        // Условный оператор для определения типа ресурса
        // Выполняется только на этапе компиляции
        if constexpr (std::is_same_v<T, sf::Texture>) {
            loadResult = resource.loadFromFile(path);
        } else if constexpr (std::is_same_v<T, sf::Font>) {
            loadResult = resource.openFromFile(path);
        }

        if (!loadResult) {
            errorLog("ResourceManager::load", "Ошибка загрузки ресурса" + name);
            return false;
        }

        resources[name] = std::move(resource);
        infoLog("ResourceManager::load", "Ресурс " + name + " успешно загружен");
        return true;
    }

    // Вырезает из текстуры с именем (sourceTextureName) прямоугольник с координатами (rect).
    // Помещает текстуру в resources с именем (name) и возвращает текстуру sf::Texture
    // Полезно, когда из тайлсета нужно вырезать один конкретный тайл
    template <typename T = Resource>
    std::enable_if_t<std::is_same_v<T, sf::Texture>, sf::Texture&>
    getSubTexture(std::string sourceTextureName, std::string name, const sf::IntRect& rect) {
        auto it = resources.find(name);
        if (it != resources.end()) return it->second;

        const auto& sourceTexture = get(sourceTextureName);

        sf::Texture subTexture;
        if (!subTexture.loadFromImage(sourceTexture.copyToImage(), false, rect)) {
            errorLog("ResourceManager::getSubTexture", "Ошибка загрузки подтекстуры");
            throw std::runtime_error("Failed to load subtexture");
        }
        resources[name] = std::move(subTexture);

        infoLog("ResourceManager::getSubTexture", "Подтекстура " + name + " успешно загружена");
        return resources[name];
    }
};