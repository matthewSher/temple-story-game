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
    std::map<std::string, Resource> resources;  // В этот словарь помещаются все загруженные ресурсы

public:
    // Метод для загрузки ресурсов. Принимает в качестве аргументов
    // название ресурса (name) и путь к нему (path)
    bool load(const std::string& name, const std::string& path) {
        if (resources.find(name) != resources.end()) {
            errorLog("ResourceManager::load", "Ресурс уже загружен");
            return false;
        }
    
        Resource resource;
        if (!resource.loadFromFile(path)) {
            errorLog("ResourceManager::load", "Ошибка загрузки ресурса");
            return false;
        }
    
        // Помещаем ресурс в map
        resources[name] = std::move(resource);

        infoLog("ResourceManager::load", "Ресурс " + name + " успешно загружен");
        return true;
    }

    // Метод, по которому можно получить соответствующий ресурс.
    // В качестве параметра передаётся название ресурса (name)
    Resource& get(const std::string& name) {
        auto it = resources.find(name); // Ищет ресурс по имени внутри map
    
        // Если ресурс не найден
        if (it == resources.end()) {
            errorLog("ResourceManager::get", "Ресурс не найден");
            throw std::runtime_error("Resources not found: " + name);
        }
    
        // Если ресурс найден, it указывает на пару ключ-значение std::pair<std::string, Resource>.
        // Возвращаем сам ресурс, т.е. второе значение

        infoLog("ResourceManager::get", "Ресурс " + name + " успешно получен");
        return it->second;
    }

    // Вырезает из текстуры с именем (sourceTextureName) прямоугольник с координатами (rect).
    // Помещает текстуру в resources с именем (name) и возвращает текстуру sf::Texture
    // Полезно, когда из тайлсета нужно вырезать один конкретный тайл
    template <typename T = Resource>
    std::enable_if_t<std::is_same_v<T, sf::Texture>, sf::Texture&>
    getSubTexture(const std::string& sourceTextureName, const std::string& name, const sf::IntRect& rect) {
        infoLog("ResourceManager::getSubTexture", "Вызван метод");

        auto it = resources.find(name);
        if (it != resources.end()) return it->second;

        const auto& sourceTexture = get(sourceTextureName);

        sf::Texture subTexture;
        if (!subTexture.loadFromImage(sourceTexture.copyToImage(), false, rect)) {
            errorLog("ResourceManager::getSubTexture", "Ошибка загрузки подтекстуры: " + name);
            throw std::runtime_error("Failed to load subtexture: " + name);
        }
        resources[name] = std::move(subTexture);

        infoLog("ResourceManager::getSubTexture", "Подтекстура " + name + " получена");
        return resources[name];
    }
};